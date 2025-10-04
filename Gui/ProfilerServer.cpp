#include "ProfilerServer.h"
#include <QDataStream>

ProfilerServer::ProfilerServer(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &ProfilerServer::handleNewConnection);
}

bool ProfilerServer::startServer(quint16 port)
{
    if (server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server: ? Escuchando en el puerto" << port;
        return true;
    }
    else
    {
        qDebug() << "Server: ? Error al iniciar en el puerto" << port << "-" << server->errorString();
        emit error(server->errorString());
        return false;
    }
}

void ProfilerServer::stopServer()
{
    for (QTcpSocket* socket : clientSockets)
    {
        socket->disconnectFromHost();
    }
    qDeleteAll(clientSockets);
    clientSockets.clear();

    server->close();
    qDebug() << "Server: Servidor detenido";
}

bool ProfilerServer::isRunning() const
{
    return server->isListening();
}

void ProfilerServer::handleNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    
    connect(clientSocket, &QTcpSocket::disconnected, this, &ProfilerServer::handleClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ProfilerServer::handleReadyRead);
    connect(clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ProfilerServer::handleError);

    clientSockets.append(clientSocket);
    
    qDebug() << "Server: ? Nuevo cliente conectado desde" << clientSocket->peerAddress().toString();
    emit clientConnected(clientSocket);
}

void ProfilerServer::handleClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        clientSockets.removeOne(socket);
        socket->deleteLater();
        qDebug() << "Server: Cliente desconectado";
        emit clientDisconnected();
    }
}

void ProfilerServer::handleReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket)
    {
        processIncomingData(socket);
    }
}

void ProfilerServer::processIncomingData(QTcpSocket *socket)
{
    QDataStream stream(socket);
    stream.setByteOrder(QDataStream::BigEndian);

    while (socket->bytesAvailable() >= sizeof(quint16) + sizeof(quint32))
    {
        // Leemos los tamaños del mensaje
        if (stream.atEnd())
            return;

        quint16 keywordLength;
        quint32 dataLength;
        stream >> keywordLength >> dataLength;

        // Verificar si tenemos suficientes datos
        if (socket->bytesAvailable() < keywordLength + dataLength)
            return;

        // Leer keyword
        QByteArray keywordBytes = socket->read(keywordLength);
        QString keyword = QString::fromUtf8(keywordBytes);

        // Leer datos
        QByteArray data = socket->read(dataLength);

        qDebug() << "Server: Recibido mensaje con keyword:" << keyword 
                 << "y tamaño de datos:" << dataLength;

        emit dataReceived(keyword, data);
    }
}

void ProfilerServer::handleError(QAbstractSocket::SocketError error)
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QString errorString = socket ? socket->errorString() : "Error desconocido";
    qDebug() << "Server: ? Error de socket:" << errorString;
    emit this->error(errorString);
}