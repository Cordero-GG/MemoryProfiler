#pragma once
#include <QTcpSocket>
#include <QString>
#include <QDataStream>

class ProfilerNotifier {
public:
    ProfilerNotifier();
    ~ProfilerNotifier() = default;

    void enviarAsignacion(void* ptr, size_t size, const QString& file, int line);
    void enviarLiberacion(void* ptr);
    void enviarResumen(qint64 memoriaTotal, qint64 cantidadGuardados, qint64 maxMemoriaUsada, qint64 totalAsignaciones);
    void enviarReportePorArchivo();

    bool estaConectado() const { return socket.state() == QAbstractSocket::ConnectedState; }

private:
    QTcpSocket socket;
    void enviarMensaje(const QString& keyword, const QByteArray& data);
};