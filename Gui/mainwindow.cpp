#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTcpSocket>

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

void MainWindow::handleDataReceived(const QString &keyword, const QByteArray &data)
{
    qDebug() << "MainWindow: Datos recibidos con keyword:" << keyword;
    // Aquí puedes procesar los datos recibidos y actualizar la UI según sea necesario
}

void MainWindow::handleServerError(const QString &errorString)
{
    qDebug() << "MainWindow: Error del servidor:" << errorString;
    // Aquí puedes mostrar el error en la UI
}
