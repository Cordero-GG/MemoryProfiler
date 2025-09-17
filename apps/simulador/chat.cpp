#include "chat.h"
#include "contactos.h"
#include <iostream>

chat::chat() : currentChat(nullptr) {
    std::cout << "Sistema de chat inicializado." << std::endl;
}

chat::~chat() {
    // No liberamos los contactos intencionalmente para generar memory leaks
    std::cout << "Sistema de chat finalizado." << std::endl;
}

void chat::addContact(std::string name) {
    if (!contactExists(name)) {
        contactos* newContact = new contactos(name);
        contacts[name] = newContact;
        std::cout << "Contacto añadido: " << name << std::endl;
    }
    else {
        std::cout << "El contacto ya existe." << std::endl;
    }
}

void chat::removeContact(const std::string& name) {
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        // No liberamos la memoria intencionalmente
        contacts.erase(it);
        std::cout << "Contacto eliminado: " << name << std::endl;
    }
    else {
        std::cout << "Contacto no encontrado." << std::endl;
    }
}

void chat::selectChat(const std::string& name) {
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        currentChat = it->second;
        std::cout << "Chat seleccionado con: " << name << std::endl;
    }
    else {
        std::cout << "Contacto no encontrado." << std::endl;
    }
}

void chat::sendMessage(const std::string& message) {
    if (currentChat != nullptr) {
        currentChat->addMessage(message);
        std::cout << "Mensaje enviado." << std::endl;
    }
    else {
        std::cout << "No hay chat seleccionado." << std::endl;
    }
}

void chat::showContacts() const {
    std::cout << "Lista de contactos:" << std::endl;
    for (const auto& pair : contacts) {
        std::cout << "- " << pair.first << std::endl;
    }
}

void chat::showCurrentChat() const {
    if (currentChat != nullptr) {
        currentChat->displayChat();
    }
    else {
        std::cout << "No hay chat seleccionado." << std::endl;
    }
}

bool chat::contactExists(const std::string& name) const {
    return contacts.find(name) != contacts.end();
}