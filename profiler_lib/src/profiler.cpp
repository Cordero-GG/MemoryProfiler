#include <iostream>
#include <chrono>
#include <mutex>
#include <QString>
#include <QDateTime>
#include "profiler.h"
#include "profilerNotifier.h"

// Inicializar las variables estáticas
QtMemoryMap Profiler::Metadatos;
std::mutex Profiler::mutexMetadatos;
qint64 Profiler::memoriaTotal = 0;
qint64 Profiler::cantidadGuardados = 0;
qint64 Profiler::maxMemoriaUsada = 0;
qint64 Profiler::totalAsignaciones = 0;
// Inicializar el notifier
ProfilerNotifier* Profiler::notifier = nullptr;


void Profiler::inicializarNotifier() {
    if (!notifier) {
        notifier = new ProfilerNotifier();  
    }
}

// Implementación de TomarInformacion
void Profiler::TomarInformacion(void* ptr, size_t size, const char* file, int line) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);

    QtMemoryInfo info;
    info.size = size;
    info.timestamp = QDateTime::currentDateTime();
    info.file = QString::fromUtf8(file ? file : "unknown");
    info.line = line;

    Metadatos[reinterpret_cast<quintptr>(ptr)] = info;
    memoriaTotal += size;
    cantidadGuardados++;
    totalAsignaciones++;

    if (memoriaTotal > maxMemoriaUsada) {
        maxMemoriaUsada = memoriaTotal;
    }

    // Inicializar automáticamente el notifier en la PRIMERA asignación
    if (!notifier) {
        inicializarNotifier();
    }

    if (notifier && notifier->estaConectado()) {
        notifier->enviarAsignacion(ptr, size, QString::fromUtf8(file ? file : "unknown"), line);

        // Enviar resumen cada 10 asignaciones (alternativa simple al timer)
        if (totalAsignaciones % 10 == 0) {
            notifier->enviarResumen(memoriaTotal, cantidadGuardados, maxMemoriaUsada, totalAsignaciones);
            notifier->enviarReportePorArchivo();
        }
    }
}

// Implementación de EliminarInformacion
void Profiler::EliminarInformacion(void* ptr) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    auto it = Metadatos.find(reinterpret_cast<quintptr>(ptr));
    if (it != Metadatos.end()) {
        memoriaTotal -= it.value().size;
        Metadatos.remove(it.key());
        cantidadGuardados--;

        if (notifier && notifier->estaConectado()) {
            notifier->enviarLiberacion(ptr);

            // Enviar resumen cada 10 liberaciones
            if (totalAsignaciones % 10 == 0) {
                notifier->enviarResumen(memoriaTotal, cantidadGuardados, maxMemoriaUsada, totalAsignaciones);
                notifier->enviarReportePorArchivo();
            }
        }
    }
}

// Implementación de tomarMemoriaTotal
qint64 Profiler::tomarMemoriaTotal() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return memoriaTotal;
}

// Implementación de tomarCantidadGuardados
qint64 Profiler::tomarCantidadGuardados() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return cantidadGuardados;
}

// Implementación de tomarMaxMemoriaUsada
qint64 Profiler::tomarMaxMemoriaUsada() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return maxMemoriaUsada;
}

// Implementación de tomarTotalAsignaciones
qint64 Profiler::tomarTotalAsignaciones() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return totalAsignaciones;
}

// Implementación de obtenerResumenPorArchivo
QtFileSummaryMap Profiler::obtenerResumenPorArchivo() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    QtFileSummaryMap summary;

    for (auto it = Metadatos.begin(); it != Metadatos.end(); ++it) {
        const auto &info = it.value();
        auto &fileSummary = summary[info.file];
        fileSummary.countAndSize.first += 1;
        fileSummary.countAndSize.second += info.size;
    }

    return summary;
}

// Implementación de ReportarMemoryLeaks
/*void Profiler::ReportarMemoryLeaks() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    if (Metadatos.isEmpty()) {
        std::cout << "No hay memory leaks" << std::endl;
    }
    else {
        std::cout << Metadatos.size() << " MEMORY LEAKS DETECTADOS:" << std::endl;
        for (auto it = Metadatos.begin(); it != Metadatos.end(); ++it) {
            const auto &info = it.value();
            QDateTime ahora = QDateTime::currentDateTime();
            qint64 duracion = info.timestamp.secsTo(ahora);
            std::cout << reinterpret_cast<void*>(it.key()) << " - " << info.size
                << " bytes (hace " << duracion << " segundos) en "
                << info.file.toStdString() << ":" << info.line << std::endl;
        }

        std::cout << "Total de memoria fugada: " << memoriaTotal << " bytes" << std::endl;
    }
}*/

// =============================================
// Implementación de ReportarMemoryLeaks
// =============================================
void Profiler::ReportarMemoryLeaks() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);

    if (Metadatos.isEmpty()) {
        std::cout << "No hay memory leaks" << std::endl;
        return;
    }

    std::cout << "\n=== MEMORY LEAKS REPORT ===" << std::endl;
    std::cout << Metadatos.size() << " MEMORY LEAKS DETECTADOS:" << std::endl;

    for (auto it = Metadatos.begin(); it != Metadatos.end(); ++it) {
        const auto& info = it.value();
        QDateTime ahora = QDateTime::currentDateTime();
        qint64 duracion = info.timestamp.secsTo(ahora);

        std::cout << "Leak: " << reinterpret_cast<void*>(it.key())
            << " - Size: " << info.size << " bytes"
            << " - Location: " << info.file.toStdString() << ":" << info.line
            << " - Age: " << duracion << " seconds" << std::endl;
    }

    std::cout << "Total leaked memory: " << memoriaTotal << " bytes ("
        << (memoriaTotal / (1024.0 * 1024.0)) << " MB)" << std::endl;
    std::cout << "============================\n" << std::endl;
}