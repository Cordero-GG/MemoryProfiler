cmake_minimum_required(VERSION 3.10)
project(simulador)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt
find_package(Qt6 REQUIRED COMPONENTS Core Network)

# Fuentes del simulador
set(SIMULADOR_SOURCES
    "src/main.cpp"
    "src/chat.cpp"
    "src/contactos.cpp"
)

# Ejecutable
add_executable(simulador
    ${SIMULADOR_SOURCES}
)

# Incluir directorios
target_include_directories(simulador PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/profiler_lib/include
)

# Enlazar con Qt y el profiler
target_link_libraries(simulador 
    profiler_lib
    Qt6::Core 
    Qt6::Network
)

# Definir USER_SOURCE para activar el macro new
target_compile_definitions(simulador PRIVATE USER_SOURCE)