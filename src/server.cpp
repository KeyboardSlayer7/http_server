#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

#include "server.h"
#include "utils.h"

Server::Server(const char* host, int port)
{
    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);
    inet_pton(AF_INET, host, &_address.sin_addr);

    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (_socket == INVALID_SOCKET)
    {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
    }

    if (bind(_socket, (SOCKADDR*)&_address, sizeof(_address)) != 0)
    {
        std::cerr << "Error binding socket: " << WSAGetLastError() << std::endl;
    }

    _buffer.resize(DEFAULT_BUFFER_LENGTH, 0);
}

Server::Server(const char* host, const char* port)
{

}

Server::~Server()
{
    closesocket(_socket); 
}

void Server::run()
{
    if (listen(_socket, BACKLOG) != 0)
    {
        printf("[ERROR] listen : %d", WSAGetLastError());
    }
    
    SOCKET client;
    SOCKADDR_IN client_address;
    int client_address_size = sizeof(client_address);

    client = accept(_socket, (SOCKADDR*)&client_address, &client_address_size);

    int bytes = recv(client, _buffer.data(), DEFAULT_BUFFER_LENGTH * sizeof(char), 0);

    if (bytes > 0)
    {
        std::string message = std::string(_buffer.data()).substr(0, bytes);
        std::cout << message;


    }
}