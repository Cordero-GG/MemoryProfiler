cmake_minimum_required(VERSION 3.16)
project(profiler_lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt (igual que en los otros CMakeLists)
find_package(Qt6 REQUIRED COMPONENTS Core Network)

# Configurar variables de salida para MSVC
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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

# Habilitar MOC automáticamente
set_target_properties(profiler_lib PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)