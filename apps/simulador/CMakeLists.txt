cmake_minimum_required(VERSION 3.10)
project(simulador)

# Ejecutable
add_executable(simulador
    "src/main.cpp"
    "src/chat.cpp"
    "src/contactos.cpp"
)

# Incluir directorios
target_include_directories(simulador PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/profiler_lib
    ${CMAKE_SOURCE_DIR}/include
)

# Enlazar con la biblioteca del profiler
target_link_libraries(simulador profiler_lib)

# Definir USER_SOURCE para que el macro se active en esta aplicación
target_compile_definitions(simulador PRIVATE USER_SOURCE)