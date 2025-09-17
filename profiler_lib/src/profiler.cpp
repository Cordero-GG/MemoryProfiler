#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include "profiler.h"
#include "socket_client.h"
#include "json_serializer.h"
#include "config.h"

using namespace std;

// Inicializar las variables est�ticas
std::unordered_map<void*, InfoMemoria> Profiler::Metadatos;
std::mutex Profiler::mutexMetadatos;
size_t Profiler::memoriaTotal = 0;
size_t Profiler::cantidadGuardados = 0;
size_t Profiler::maxMemoriaUsada = 0;
size_t Profiler::totalAsignaciones = 0;

// Hilo para m�tricas peri�dicas
static void metricsThread() {
    auto& socketClient = SocketClient::getInstance();

    while (true) {
        this_thread::sleep_for(chrono::milliseconds(METRICS_UPDATE_INTERVAL_MS));

        // Obtener m�tricas
        auto currentMemory = Profiler::tomarMemoriaTotal();
        auto activeAllocations = Profiler::tomarCantidadGuardados();
        auto totalAllocations = Profiler::tomarTotalAsignaciones();
        auto maxMemoryUsed = Profiler::tomarMaxMemoriaUsada();

        // Enviar m�tricas generales
        auto metricsJson = metricsToJson(currentMemory, activeAllocations,
            totalAllocations, maxMemoryUsed);
        socketClient.enqueueMessage(metricsJson.dump());

        // Enviar resumen por archivo
        auto fileSummary = Profiler::obtenerResumenPorArchivo();
        auto fileSummaryJson = fileSummaryToJson(fileSummary);
        socketClient.enqueueMessage(fileSummaryJson.dump());
    }
}

// Inicializador est�tico para iniciar el hilo de m�tricas
static int initMetricsThread() {
    thread t(metricsThread);
    t.detach();
    return 0;
}
static int dummy = initMetricsThread();

// Implementaci�n de TomarInformacion
void Profiler::TomarInformacion(void* ptr, size_t size, const char* file, int line) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    InfoMemoria info;
    info.size = size;
    info.timestamp = std::chrono::system_clock::now();
    info.file = file;
    info.line = line;
    Metadatos[ptr] = info;
    memoriaTotal += size;
    cantidadGuardados++;
    totalAsignaciones++;

    if (memoriaTotal > maxMemoriaUsada) {
        maxMemoriaUsada = memoriaTotal;
    }

    // Mensaje de depuraci�n
    std::cout << "Asignaci�n: " << ptr << " - " << size << " bytes en "
        << (file ? file : "unknown") << ":" << line << std::endl;

    // Enviar informaci�n de asignaci�n
    auto json = allocationToJson(ptr, size, file, line);
    SocketClient::getInstance().enqueueMessage(json.dump());
}

// Implementaci�n de EliminarInformacion
void Profiler::EliminarInformacion(void* ptr) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    auto it = Metadatos.find(ptr);
    if (it != Metadatos.end()) {
        memoriaTotal -= it->second.size;
        Metadatos.erase(it);
        cantidadGuardados--;

        // Mensaje de depuraci�n
        std::cout << "Liberaci�n: " << ptr << std::endl;

        // Enviar informaci�n de liberaci�n
        auto json = deallocationToJson(ptr);
        SocketClient::getInstance().enqueueMessage(json.dump());
    }
}

// Implementaci�n de tomarMemoriaTotal
std::size_t Profiler::tomarMemoriaTotal() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return memoriaTotal;
}

// Implementaci�n de tomarCantidadGuardados
std::size_t Profiler::tomarCantidadGuardados() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return cantidadGuardados;
}

// Implementaci�n de tomarMaxMemoriaUsada
std::size_t Profiler::tomarMaxMemoriaUsada() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return maxMemoriaUsada;
}

// Implementaci�n de tomarTotalAsignaciones
std::size_t Profiler::tomarTotalAsignaciones() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return totalAsignaciones;
}

// Implementaci�n de obtenerResumenPorArchivo
std::unordered_map<std::string, std::pair<size_t, size_t>> Profiler::obtenerResumenPorArchivo() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    std::unordered_map<std::string, std::pair<size_t, size_t>> summary;

    for (const auto& [ptr, info] : Metadatos) {
        auto it = summary.find(info.file);
        if (it != summary.end()) {
            it->second.first += 1;
            it->second.second += info.size;
        }
        else {
            summary[info.file] = { 1, info.size };
        }
    }

    return summary;
}

// Implementaci�n de ReportarMemoryLeaks
void Profiler::ReportarMemoryLeaks() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    if (Metadatos.empty()) {
        std::cout << "No hay memory leaks" << std::endl;

        // Enviar reporte vac�o
        auto json = leakReportToJson(Metadatos, 0);
        SocketClient::getInstance().enqueueMessage(json.dump());
    }
    else {
        // Enviar reporte de leaks
        auto json = leakReportToJson(Metadatos, memoriaTotal);
        SocketClient::getInstance().enqueueMessage(json.dump());

        std::cout << Metadatos.size() << " MEMORY LEAKS DETECTADOS:" << std::endl;
        for (const auto& [direccion, info] : Metadatos) {
            auto ahora = std::chrono::system_clock::now();
            auto duracion = std::chrono::duration_cast<std::chrono::seconds>(ahora - info.timestamp);
            std::cout << direccion << " - " << info.size
                << " bytes (hace " << duracion.count() << " segundos) en "
                << info.file << ":" << info.line << std::endl;
        }

        std::cout << "Total de memoria fugada: " << memoriaTotal << " bytes" << std::endl;
    }
}