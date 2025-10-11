cmake_minimum_required(VERSION 3.16)
project(MemoryProfiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt - especificar explícitamente los componentes necesarios
find_package(Qt6 REQUIRED COMPONENTS Core Network)

# Configurar variables de salida - MÁS SIMPLE
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Para MSVC, deshabilitar algunas advertencias si es necesario
if(MSVC)
    add_compile_options(/W4)
endif()

# Agregar subdirectorios en ORDEN CORRECTO
add_subdirectory(profiler_lib)
add_subdirectory(apps/simulador)