#define USER_SOURCE
#include "../../../profiler_lib/include/profiler.h"
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
    // INICIALIZAR EL PROFILER AL INICIO
    std::cout << "Inicializando Memory Profiler..." << std::endl;
    Profiler::inicializarNotifier(); 
	std::cout << "Paso?" << std::endl;

    showMenu();

    // Lógica del chat con memory leaks intencionales
    chat sistemaChat;

    // Agregar contactos (algunos con leaks)
    sistemaChat.addContact("Usuario1");
    sistemaChat.addContact("Usuario2");
    sistemaChat.addContact("Usuario3"); // Este tendrá leak

    // Seleccionar chat y enviar mensajes
    sistemaChat.selectChat("Usuario1");
    sistemaChat.sendMessage("Hola desde el profiler!");
    sistemaChat.sendMessage("Este es un mensaje de prueba");

    // Mostrar el chat actual
    sistemaChat.showCurrentChat();

    // Mostrar todos los contactos
    sistemaChat.showContacts();

    // Eliminar un contacto (pero no todos, para generar leaks)
    sistemaChat.removeContact("Usuario2");

    std::cout << "Finalizando simulador de chat..." << std::endl;

    // Mantener el programa corriendo un tiempo para ver datos en tiempo real
    std::cout << "Presiona Enter para terminar...";
    std::cin.get();  

    // Reportar memory leaks al finalizar
    Profiler::ReportarMemoryLeaks();

    return 0;
}