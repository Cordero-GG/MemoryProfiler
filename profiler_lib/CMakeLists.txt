cmake_minimum_required(VERSION 3.16)
project(profiler_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fuentes de la biblioteca
set(PROFILER_SOURCES
    "src/profiler.cpp"
    "src/profilerNotifier.cpp"
    "src/SobrescribirOperador.cpp"
)

# Biblioteca del profiler
add_library(profiler_lib STATIC ${PROFILER_SOURCES})

# Incluir directorios
target_include_directories(profiler_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enlazar con Qt
target_link_libraries(profiler_lib
    Qt6::Core
    Qt6::Network
)

# Definir PROFILER_LIB para controlar el macro new
target_compile_definitions(profiler_lib PRIVATE PROFILER_LIB)

# Habilitar MOC automáticamente
set_target_properties(profiler_lib PROPERTIES
    AUTOMOC ON
)