#ifndef PROYECTOMEMORIA_PROFILER_H
#define PROYECTOMEMORIA_PROFILER_H

#include <mutex>
#include <cstddef>
#include <QString>
#include <QDateTime>

#include "profiler_types.h"

// Si no estamos compilando la biblioteca, definir USER_SOURCE para activar el macro
#ifndef PROFILER_LIB
#define USER_SOURCE
#endif

class Profiler {
private:
    static QtMemoryMap Metadatos;
    static std::mutex mutexMetadatos;
    static qint64 memoriaTotal;
    static qint64 cantidadGuardados;
    static qint64 maxMemoriaUsada;
    static qint64 totalAsignaciones;
	static profilerNotifier* notifier;

public:
    // Métodos de tracking
    static void TomarInformacion(void* ptr, size_t size, const char* file, int line);
    static void EliminarInformacion(void* ptr);
    static qint64 tomarMemoriaTotal();
    static qint64 tomarCantidadGuardados();
    static qint64 tomarMaxMemoriaUsada();
    static qint64 tomarTotalAsignaciones();
    static void ReportarMemoryLeaks();

    // Nuevo método para obtener resumen por archivo
    static QtFileSummaryMap obtenerResumenPorArchivo();
};

void* operator new(std::size_t size, const char* file, int line);
void operator delete(void* ptr, const char* file, int line) noexcept;
void* operator new[](std::size_t size, const char* file, int line);
void operator delete[](void* ptr, const char* file, int line) noexcept;

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void* operator new[](std::size_t size);
void operator delete[](void* ptr) noexcept;

// Solo definir el macro new en archivos de usuario si USER_SOURCE está definido y no se deshabilita
#if defined(USER_SOURCE) && !defined(DISABLE_PROFILER_MACRO)
#define new new(__FILE__, __LINE__)
#endif

#endif