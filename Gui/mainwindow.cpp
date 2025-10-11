#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTcpSocket>
#include <QTableWidgetItem>
#include <QFileInfo>  
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server(new ProfilerServer(this))
{
    ui->setupUi(this);

    // Conectar señales del servidor
    connect(server, &ProfilerServer::clientConnected, this, &MainWindow::handleClientConnected);
    connect(server, &ProfilerServer::clientDisconnected, this, &MainWindow::handleClientDisconnected);
    connect(server, &ProfilerServer::dataReceived, this, &MainWindow::handleDataReceived);
    connect(server, &ProfilerServer::error, this, &MainWindow::handleServerError);

    // Iniciar el servidor al arrancar la aplicación
    if (!server->startServer(8080))
    {
        qDebug() << "Error: No se pudo iniciar el servidor de profiling";
    }
}

MainWindow::~MainWindow()
{
    if (server->isRunning())
    {
        server->stopServer();
    }
    delete ui;
}

void MainWindow::handleClientConnected(QTcpSocket *socket)
{
    qDebug() << "MainWindow: Cliente conectado desde" << socket->peerAddress().toString();
    // Aquí puedes actualizar la UI para mostrar el cliente conectado
}

void MainWindow::handleClientDisconnected()
{
    qDebug() << "MainWindow: Cliente desconectado";
    // Aquí puedes actualizar la UI para mostrar que el cliente se desconectó
}



void MainWindow::handleServerError(const QString &errorString)
{
    qDebug() << "MainWindow: Error del servidor:" << errorString;
    // Aquí puedes mostrar el error en la UI
}





void MainWindow::handleDataReceived(const QString& keyword, const QByteArray& data) {
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::BigEndian);

    if (keyword == "ALLOC") {
        // Procesar asignación
        quintptr address;
        quint64 size;
        QString file;
        int line;

        stream >> address >> size >> file >> line;

        qDebug() << "Asignacion:" << reinterpret_cast<void*>(address)
            << "Tamano:" << size << "Archivo:" << file << "Linea:" << line;

        // ACTUALIZAR UI: Agregar a la tabla del mapa de memoria
        agregarBloqueMemoriaTabla(address, size, file, line);

    }
    else if (keyword == "FREE") {
        // Procesar liberación
        quintptr address;
        stream >> address;

        qDebug() << "Liberacion:" << reinterpret_cast<void*>(address);

        // ACTUALIZAR UI: Remover de la tabla del mapa de memoria
        removerBloqueMemoriaTabla(address);

    }
    else if (keyword == "SUMMARY") {
        // Procesar resumen
        qint64 memoriaTotal, cantidadGuardados, maxMemoriaUsada, totalAsignaciones;
        stream >> memoriaTotal >> cantidadGuardados >> maxMemoriaUsada >> totalAsignaciones;

        qDebug() << "Resumen - Memoria:" << memoriaTotal << "Activas:" << cantidadGuardados
            << "Maximo:" << maxMemoriaUsada << "Total Asignaciones:" << totalAsignaciones;

        // ACTUALIZAR UI: Actualizar métricas generales
        actualizarMetricasUI(memoriaTotal, cantidadGuardados, maxMemoriaUsada, totalAsignaciones);

        // ACTUALIZAR UI: Actualizar tabla de resumen por archivo
        actualizarResumenPorArchivo();
    }
}

void MainWindow::actualizarMetricasUI(qint64 memoriaTotal, qint64 activas, qint64 maxMemoria, qint64 totalAsignaciones) {
    // Convertir bytes a MB
    double memoriaMB = memoriaTotal / (1024.0 * 1024.0);
    double maxMemoriaMB = maxMemoria / (1024.0 * 1024.0);

    // Actualizar labels de la pestaña General
    ui->labelUsoActual->setText(QString("Uso actual de memoria: %1 MB").arg(memoriaMB, 0, 'f', 2));
    ui->labelAsignaciones->setText(QString("Asignaciones activas: %1").arg(activas));
    ui->labelMaximo->setText(QString("Uso maximo: %1 MB").arg(maxMemoriaMB, 0, 'f', 2));
    ui->labelTotalAsignaciones->setText(QString("Total asignaciones: %1").arg(totalAsignaciones));

    // Calcular y mostrar memory leaks (simplificado)
    double leaksMB = (memoriaTotal > 0) ? (memoriaTotal * 0.1) / (1024.0 * 1024.0) : 0.0;
    ui->labelLeaks->setText(QString("Memory leaks: %1 MB").arg(leaksMB, 0, 'f', 2));
}

void MainWindow::agregarBloqueMemoriaTabla(quintptr address, quint64 size, const QString& file, int line) {
    // Agregar a la tabla del Mapa de Memoria
    int row = ui->tableMapaMemoria->rowCount();
    ui->tableMapaMemoria->insertRow(row);

    ui->tableMapaMemoria->setItem(row, 0, new QTableWidgetItem(QString("0x%1").arg(address, 16, 16, QChar('0'))));
    ui->tableMapaMemoria->setItem(row, 1, new QTableWidgetItem(QString::number(size)));
    ui->tableMapaMemoria->setItem(row, 2, new QTableWidgetItem("Unknown"));
    ui->tableMapaMemoria->setItem(row, 3, new QTableWidgetItem("Activo"));

    // Extraer solo el nombre del archivo, no la ruta completa
    QString nombreArchivo = file;
    if (!file.isEmpty()) {
        QFileInfo fileInfo(file);
        nombreArchivo = fileInfo.fileName();
    }
    ui->tableMapaMemoria->setItem(row, 4, new QTableWidgetItem(QString("%1:%2").arg(nombreArchivo).arg(line)));

    // Mantener referencia para luego poder remover
    QVector<QString> bloqueInfo;
    bloqueInfo << QString::number(size) << file << QString::number(line) << "Unknown";
    bloquesMemoria[address] = bloqueInfo;

    // Actualizar resumen por archivo
    if (!resumenArchivos.contains(nombreArchivo)) {
        resumenArchivos[nombreArchivo] = QPair<int, qint64>(0, 0);
    }
    resumenArchivos[nombreArchivo].first += 1;
    resumenArchivos[nombreArchivo].second += size;
}

void MainWindow::removerBloqueMemoriaTabla(quintptr address) {
    // Remover de la tabla del Mapa de Memoria
    for (int i = 0; i < ui->tableMapaMemoria->rowCount(); ++i) {
        QTableWidgetItem* item = ui->tableMapaMemoria->item(i, 0);
        if (item && item->text() == QString("0x%1").arg(address, 16, 16, QChar('0'))) {
            ui->tableMapaMemoria->removeRow(i);

            // Actualizar resumen por archivo
            if (bloquesMemoria.contains(address)) {
                QVector<QString> info = bloquesMemoria[address];
                QString filePath = info[1];
                QString nombreArchivo = filePath;
                if (!filePath.isEmpty()) {
                    QFileInfo fileInfo(filePath);
                    nombreArchivo = fileInfo.fileName();
                }
                quint64 size = info[0].toULongLong();

                if (resumenArchivos.contains(nombreArchivo)) {
                    resumenArchivos[nombreArchivo].first -= 1;
                    resumenArchivos[nombreArchivo].second -= size;

                    // Si no hay más asignaciones de este archivo, removerlo
                    if (resumenArchivos[nombreArchivo].first <= 0) {
                        resumenArchivos.remove(nombreArchivo);
                    }
                }

                bloquesMemoria.remove(address);
            }
            break;
        }
    }
}

void MainWindow::actualizarResumenPorArchivo() {
    // Limpiar tabla de resumen por archivo
    ui->tableAsignacionesArchivo->setRowCount(0);

    // Llenar con datos actualizados
    int row = 0;
    QHash<QString, QPair<int, qint64>>::iterator it;
    for (it = resumenArchivos.begin(); it != resumenArchivos.end(); ++it) {
        ui->tableAsignacionesArchivo->insertRow(row);

        QString archivo = it.key();
        int count = it.value().first;
        double totalMB = it.value().second / (1024.0 * 1024.0);

        ui->tableAsignacionesArchivo->setItem(row, 0, new QTableWidgetItem(archivo));
        ui->tableAsignacionesArchivo->setItem(row, 1, new QTableWidgetItem(QString::number(count)));
        ui->tableAsignacionesArchivo->setItem(row, 2, new QTableWidgetItem(QString::number(totalMB, 'f', 2)));

        row++;
    }

    // También actualizar la tabla Top 3 en la pestaña General
    actualizarTop3Archivos();
}

void MainWindow::actualizarTop3Archivos() {
    // Limpiar tabla top 3
    ui->tableTopArchivos->setRowCount(0);

    // Ordenar archivos por memoria total (descendente)
    QList<QPair<QString, qint64>> archivosOrdenados;
    QHash<QString, QPair<int, qint64>>::iterator it;
    for (it = resumenArchivos.begin(); it != resumenArchivos.end(); ++it) {
        archivosOrdenados.append(QPair<QString, qint64>(it.key(), it.value().second));
    }

    // Ordenar manualmente (evitando std::sort si hay problemas)
    for (int i = 0; i < archivosOrdenados.size() - 1; ++i) {
        for (int j = i + 1; j < archivosOrdenados.size(); ++j) {
            if (archivosOrdenados[i].second < archivosOrdenados[j].second) {
                archivosOrdenados.swapItemsAt(i, j);
            }
        }
    }

    // Tomar top 3
    int count = qMin(3, archivosOrdenados.size());
    for (int i = 0; i < count; ++i) {
        ui->tableTopArchivos->insertRow(i);

        QString archivo = archivosOrdenados[i].first;
        double totalMB = archivosOrdenados[i].second / (1024.0 * 1024.0);

        // Contar asignaciones para este archivo
        int numAsignaciones = resumenArchivos[archivo].first;

        ui->tableTopArchivos->setItem(i, 0, new QTableWidgetItem(archivo));
        ui->tableTopArchivos->setItem(i, 1, new QTableWidgetItem(QString::number(numAsignaciones)));
        ui->tableTopArchivos->setItem(i, 2, new QTableWidgetItem(QString::number(totalMB, 'f', 2)));
    }
}



