#define DISABLE_PROFILER_MACRO // Evita que el macro de profiler.h afecte este archivo
#include <new>
#include <cstdlib>
#include <iostream>
#include "profiler.h"

// ===== SOBRECARGAS CON FILE/LINE =====
void* operator new(std::size_t size, const char* file, int line) {
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    Profiler::TomarInformacion(ptr, size, file, line);
    return ptr;
}

void* operator new[](std::size_t size, const char* file, int line) {
    return operator new(size, file, line);
}

void operator delete(void* ptr, const char* file, int line) noexcept {
    if (ptr) {
        Profiler::EliminarInformacion(ptr);
    }
    std::free(ptr);
}

void operator delete[](void* ptr, const char* file, int line) noexcept {
    operator delete(ptr, file, line);
}

// ===== SOBRECARGAS STANDARD =====
void* operator new(std::size_t size) {
    return operator new(size, "unknown", 0);
}

void* operator new[](std::size_t size) {
    return operator new(size, "unknown", 0);
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        Profiler::EliminarInformacion(ptr);
    }
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}

// Versiones no-throw
void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
    void* ptr = std::malloc(size);
    if (ptr) {
        Profiler::TomarInformacion(ptr, size, "unknown", 0);
    }
    return ptr;
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    return operator new(size, std::nothrow);
}