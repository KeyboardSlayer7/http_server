#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <fstream>

#include "server.h"
#include "utils.h"
#include "http_parser.h"

#include "nlohmann/json.hpp"

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

    std::ifstream file("../config.json");     
    _content_types = json::parse(file);
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

    while (true)
    {
        SOCKET client;
        SOCKADDR_IN client_address;
        int client_address_size = sizeof(client_address);
    
        client = accept(_socket, (SOCKADDR*)&client_address, &client_address_size);
    
        int bytes = recv(client, _buffer.data(), DEFAULT_BUFFER_LENGTH * sizeof(char), 0);
    
        if (bytes > 0)
        {
            std::string message = std::string(_buffer.data()).substr(0, bytes);
            std::cout << message;
    
            Http parsed_request = parse(message);

            std::string resource = (parsed_request.get("path") == "/") ? "../index.html" : "../" + (parsed_request.get("path").erase(0, 1)); 

            Content content;
            int index = resource.find('.', 3);
            
            // std::cout << _content_types["content_type"] << "\n";
            std::cout << "Resource: " << resource << "\n";
            std::cout << "substr: " << resource.substr(index + 1, resource.size() - index) << "\n";

            content.type = _content_types["content_type"][resource.substr(index + 1, resource.size() - index)];
            content.data = get_content(resource.c_str()); 

            // std::cout << "ct: " << content.type << "\n";

            std::string response = createResponse(parsed_request, content);
            
            std::cout << response;

            int bytes_sent = 0;

            bytes_sent += send(client, response.c_str(), response.size(), 0);
            bytes_sent += send(client, content.data.data(), content.data.size(), 0);

            if (bytes_sent <= 0)
            {
                printf("[ERROR] send failed!\n");
                std::cout << "[ERROR] : " << WSAGetLastError();
            }

            closesocket(client);   
        }
    } 
}

std::string Server::createResponse(Http& http, Content& content)
{
    std::string response = http.get("http_version");

    if (content.data.size() > 0)
    {
        response += " 200 OK\r\n";
    }
    else
    {
        response += " 404 Not Found\r\n";
    }

    auto time = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(time);

    std::string time_string = std::ctime(&time_now);
    time_string.erase(time_string.end() - 1);

    response += "Date: " + time_string + "\r\n";
    response += "Server: Http_Server v0.1\r\n";
    response += "Content-Length: " + std::to_string(content.data.size()) + "\r\n";
    response += "Content-Type: " + content.type + "\r\n";
    response += "Connection: close\r\n";
    response += "\r\n";

    return response;
}