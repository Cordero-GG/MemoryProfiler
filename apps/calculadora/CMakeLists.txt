cmake_minimum_required(VERSION 3.10)
project(calculadora)

# Ejecutable
add_executable(calculadora
    "src/main.cpp"
    "src/Calculadora.cpp"
    "src/Potencia.cpp"
)

# Incluir directorios
target_include_directories(calculadora PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/profiler_lib
    ${CMAKE_SOURCE_DIR}/include
)

# Enlazar con la biblioteca del profiler
target_link_libraries(calculadora profiler_lib)

# Definir USER_SOURCE para que el macro se active en esta aplicación
target_compile_definitions(calculadora PRIVATE USER_SOURCE)