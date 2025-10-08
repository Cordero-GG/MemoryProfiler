#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class ProfilerNotifier : public QObject {
    Q_OBJECT
public:
    explicit ProfilerNotifier(QObject* parent = nullptr);

    void enviarAsignacion(void* ptr, size_t size, const QString& file, int line);
    void enviarLiberacion(void* ptr);
    void enviarResumen(qint64 memoriaTotal, qint64 cantidadGuardados, qint64 maxMemoriaUsada, qint64 totalAsignaciones);

private:
    QTcpSocket socket;
    void enviarMensaje(const QJsonObject& obj);
};
