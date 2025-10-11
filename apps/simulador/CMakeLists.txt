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
    "include/chat.h"
    "include/contactos.h"
)

# Ejecutable
add_executable(simulador
    "src/main.cpp"
    "src/chat.cpp"
    "src/contactos.cpp"
    "include/chat.h"
    "include/contactos.h"
)

# Incluir directorios
target_include_directories(simulador PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include              #Header del simulador
    ${CMAKE_SOURCE_DIR}/profiler_lib/include         #Header del profiler
)



# Enlazar con Qt y el profiler
target_link_libraries(simulador 
   
    Qt6::Core 
    Qt6::Network
)

# Definir USER_SOURCE y USE_QT
target_compile_definitions(simulador PRIVATE USER_SOURCE USE_QT)