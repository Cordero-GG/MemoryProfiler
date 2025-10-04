#ifndef PROFILERSERVER_H
#define PROFILERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class ProfilerServer : public QObject
{
    Q_OBJECT
public:
    explicit ProfilerServer(QObject *parent = nullptr);
    bool startServer(quint16 port = 8080);
    void stopServer();
    bool isRunning() const;

signals:
    void clientConnected(QTcpSocket *socket);
    void clientDisconnected();
    void dataReceived(const QString &keyword, const QByteArray &data);
    void error(const QString &errorString);

private slots:
    void handleNewConnection();
    void handleClientDisconnected();
    void handleReadyRead();
    void handleError(QAbstractSocket::SocketError error);

private:
    QTcpServer *server;
    QList<QTcpSocket*> clientSockets;

    void processIncomingData(QTcpSocket *socket);
};

#endif // PROFILERSERVER_H