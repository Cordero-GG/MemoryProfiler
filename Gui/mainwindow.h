#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
};
#endif // MAINWINDOW_H
