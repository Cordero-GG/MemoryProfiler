#define USER_SOURCE
#include <profiler.h>
#include <iostream>
#include <string>
#include "../include/chat.h"

void showMenu() {
    std::cout << "\n=== SISTEMA DE CHAT ===\n";
    std::cout << "1. Agregar contacto\n";
    std::cout << "2. Eliminar contacto\n";
    std::cout << "3. Seleccionar chat\n";
    std::cout << "4. Enviar mensaje\n";
    std::cout << "5. Mostrar contactos\n";
    std::cout << "6. Mostrar chat actual\n";
    std::cout << "0. Salir\n";
}

int main() {
    showMenu();
    // Aquí iría la lógica de interacción con la clase chat
    return 0;
}