#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QPair>
#include <QVector>
#include <QString>
#include <QFileInfo> 
#include "ProfilerServer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleClientConnected(QTcpSocket *socket);
    void handleClientDisconnected();
    void handleDataReceived(const QString &keyword, const QByteArray &data);
    void handleServerError(const QString &errorString);
    

private:
    Ui::MainWindow *ui;
    ProfilerServer *server;

    void actualizarMetricasUI(qint64 memoriaTotal, qint64 activas, qint64 maxMemoria, qint64 totalAsignaciones);
    void agregarBloqueMemoriaTabla(quintptr address, quint64 size, const QString& file, int line);
    void removerBloqueMemoriaTabla(quintptr address);
    void actualizarResumenPorArchivo();
    void actualizarTop3Archivos();

    // Estructuras para mantener el estado
    QHash<quintptr, QVector<QString>> bloquesMemoria; // address -> [size, file, line, type]
    QHash<QString, QPair<int, qint64>> resumenArchivos; // filename -> [count, totalSize]
};
#endif // MAINWINDOW_H
