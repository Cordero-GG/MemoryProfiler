#include "ProfilerNotifier.h"

ProfilerNotifier::ProfilerNotifier(QObject* parent) : QObject(parent) {
    socket.connectToHost("127.0.0.1", 8080); // Cambia el puerto si es necesario
}

void ProfilerNotifier::enviarAsignacion(void* ptr, size_t size, const QString& file, int line) {
    QJsonObject obj;
    obj["tipo"] = "asignacion";
    obj["ptr"] = QString::number(reinterpret_cast<quintptr>(ptr));
    obj["size"] = static_cast<qint64>(size);
    obj["file"] = file;
    obj["line"] = line;
    enviarMensaje(obj);
}

void ProfilerNotifier::enviarLiberacion(void* ptr) {
    QJsonObject obj;
    obj["tipo"] = "liberacion";
    obj["ptr"] = QString::number(reinterpret_cast<quintptr>(ptr));
    enviarMensaje(obj);
}

void ProfilerNotifier::enviarResumen(qint64 memoriaTotal, qint64 cantidadGuardados, qint64 maxMemoriaUsada, qint64 totalAsignaciones) {
    QJsonObject obj;
    obj["tipo"] = "resumen";
    obj["memoriaTotal"] = memoriaTotal;
    obj["cantidadGuardados"] = cantidadGuardados;
    obj["maxMemoriaUsada"] = maxMemoriaUsada;
    obj["totalAsignaciones"] = totalAsignaciones;
    enviarMensaje(obj);
}

void ProfilerNotifier::enviarMensaje(const QJsonObject& obj) {
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";
    socket.write(data);
    socket.flush();
}
