#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QDataStream>

class ProfilerNotifier : public QObject {
    Q_OBJECT
public:
    explicit ProfilerNotifier(QObject* parent = nullptr);

    void enviarAsignacion(void* ptr, size_t size, const QString& file, int line);
    void enviarLiberacion(void* ptr);
    void enviarResumen(qint64 memoriaTotal, qint64 cantidadGuardados, qint64 maxMemoriaUsada, qint64 totalAsignaciones);
    void enviarReportePorArchivo();

private:
    QTcpSocket socket;
    void enviarMensaje(const QString& keyword, const QByteArray& data);
};
