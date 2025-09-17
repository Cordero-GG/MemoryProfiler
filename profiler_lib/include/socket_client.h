#ifndef PROYECTOMEMORIA_SOCKET_CLIENT_H
#define PROYECTOMEMORIA_SOCKET_CLIENT_H

#pragma once

// Definiciones específicas para Windows
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>
#include <queue>
#include <mutex>
#include <thread>

// Asegurar que se enlace la librería de sockets de Windows
#pragma comment(lib, "ws2_32.lib")

class SocketClient {
public:
    static SocketClient& getInstance();
    void enqueueMessage(const std::string& message);
    bool isConnected() const;
    void stop();

private:
    SocketClient();
    ~SocketClient();
    void connect();
    void sendThread();

    SOCKET sock;
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    std::thread senderThread;
    bool connected;
    bool running;
};

#endif //PROYECTOMEMORIA_SOCKET_CLIENT_H