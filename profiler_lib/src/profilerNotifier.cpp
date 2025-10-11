#include "profilerNotifier.h"
#include "profiler.h"
#include <QDataStream>

ProfilerNotifier::ProfilerNotifier() {
    // Conexión simple sin timer
    socket.connectToHost("127.0.0.1", 8080);
}

void ProfilerNotifier::enviarAsignacion(void* ptr, size_t size, const QString& file, int line) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << reinterpret_cast<quintptr>(ptr)
        << static_cast<quint64>(size)
        << file
        << line;

    enviarMensaje("ALLOC", data);
}

void ProfilerNotifier::enviarLiberacion(void* ptr) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << reinterpret_cast<quintptr>(ptr);
    enviarMensaje("FREE", data);
}

void ProfilerNotifier::enviarResumen(qint64 memoriaTotal, qint64 cantidadGuardados,
    qint64 maxMemoriaUsada, qint64 totalAsignaciones) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << memoriaTotal
        << cantidadGuardados
        << maxMemoriaUsada
        << totalAsignaciones;

    enviarMensaje("SUMMARY", data);
}

void ProfilerNotifier::enviarReportePorArchivo() {
    auto resumen = Profiler::obtenerResumenPorArchivo();

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);

    stream << static_cast<quint32>(resumen.size());

    for (auto it = resumen.begin(); it != resumen.end(); ++it) {
        stream << it.key()
            << it.value().countAndSize.first
            << it.value().countAndSize.second;
    }

    enviarMensaje("FILE_SUMMARY", data);
}

void ProfilerNotifier::enviarMensaje(const QString& keyword, const QByteArray& data) {
    if (socket.state() == QAbstractSocket::ConnectedState) {
        QByteArray packet;
        QDataStream packetStream(&packet, QIODevice::WriteOnly);
        packetStream.setByteOrder(QDataStream::BigEndian);

        QByteArray keywordBytes = keyword.toUtf8();
        packetStream << static_cast<quint16>(keywordBytes.size())
            << static_cast<quint32>(data.size());

        packet.append(keywordBytes);
        packet.append(data);

        socket.write(packet);
        socket.flush();
    }
}