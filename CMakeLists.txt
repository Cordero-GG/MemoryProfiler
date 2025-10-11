cmake_minimum_required(VERSION 3.20)
project(MemoryProfiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar políticas de CMake
cmake_policy(SET CMP0079 NEW)

# Configurar directorios de salida
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Para MSVC - Configurar runtime
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Subproyectos en ORDEN CORRECTO
add_subdirectory(profiler_lib)
add_subdirectory(Gui)
add_subdirectory(apps/simulador)