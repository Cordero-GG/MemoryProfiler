#include "contactos.h"
#include <iostream>

contactos::contactos(const std::string& name) : name(name) {
    std::cout << "Contacto creado: " << name << std::endl;
}

contactos::~contactos() {
    // No liberamos los mensajes intencionalmente para generar memory leaks
    std::cout << "Contacto destruido: " << name << std::endl;
}

std::string contactos::getName() const {
    return name;
}

void contactos::addMessage(const std::string& message) {
    std::string* newMessage = new std::string(message);
    messages.push_back(newMessage);
}

void contactos::displayChat() const {
    std::cout << "Chat con " << name << ":" << std::endl;
    for (size_t i = 0; i < messages.size(); ++i) {
        std::cout << i + 1 << ". " << *messages[i] << std::endl;
    }
}