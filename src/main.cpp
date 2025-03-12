#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <vector>
#include <filesystem>

#include "utils.h"
#include "http_parser.h"
#include "server.h"

int main(int argc, char* argv[])
{
    WSADATA wsa_data;
    INT64 wVersionRequested = MAKEWORD(2, 2);

    if (WSAStartup(wVersionRequested, &wsa_data) != 0)
    {
        printf("[ERROR] WSAStartup Failed!\n");
        std::exit(EXIT_FAILURE);
    }

    // std::unordered_map<std::string, std::string> pages;
    // pages["/"] = "index.html";
    // pages["/image.png"] = "image.png";

    const char* ip = "127.0.0.1";
    int port = 42069;

    // SOCKET server, client;
    // SOCKADDR_IN server_address, client_address;

    // server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // server_address.sin_family = AF_INET;
    // server_address.sin_port = htons(port);
    // inet_pton(AF_INET, ip, &server_address.sin_addr);

    // bind(server, (SOCKADDR*)&server_address, sizeof(server_address));

    // char* buffer = new char[DEFAULT_BUFFER_LENGTH * sizeof(char)];

    // int client_address_size = sizeof(client_address);

    // while (true)
    // {
    //     if (listen(server, BACKLOG) != 0)
    //     {
    //         printf("[ERROR] listen : %d", WSAGetLastError());
    //     }

    //     client = accept(server, (SOCKADDR*)&client_address, &client_address_size);

    //     int bytes = recv(client, buffer, DEFAULT_BUFFER_LENGTH * sizeof(char), 0);
        
    //     if (bytes > 0)
    //     {
    //         std::string message = std::string(buffer).substr(0, bytes);
    //         std::cout << message;

    //         Http parsed_request = parse(message);

    //         std::string resource = parsed_request.get("path");
    //         std::cout << "Path: " << resource << std::endl;
    //         std::cout << pages[resource] << std::endl;
            
    //         std::string content_type;
    //         std::vector<char> content;
            
    //         if (pages[resource].find(".html") != std::string::npos)
    //         {
    //             content_type = "text/html";
    //         }
    //         else if (pages[resource].find(".png") != std::string::npos)
    //         {
    //             content_type = "image/png";
    //         }

    //         content = get_content(pages[resource].c_str());
    //         std::cout << "Body size: " << content.size() << std::endl;

    //         std::string response; // = createResponse(parsed_request, content);
            
    //         auto time = std::chrono::system_clock::now();
    //         std::time_t time_now = std::chrono::system_clock::to_time_t(time);

    //         response += parsed_request.get("http_version") + " 200 OK\r\nDate: ";
    //         response += std::ctime(&time_now);
    //         response += "Server: Http_Server v0.1\r\nContent-Length: " + std::to_string(content.size()) 
    //             + "\r\nContent-Type: " + content_type + "\r\n\r\n";
            
    //         std::cout << response;

    //         int bytes_sent = 0;

    //         bytes_sent += send(client, response.c_str(), response.size(), 0);
    //         bytes_sent += send(client, content.data(), content.size(), 0);

    //         if (bytes_sent <= 0)
    //         {
    //             printf("[ERROR] send failed!\n");
    //             std::cout << "[ERROR] : " << WSAGetLastError();
    //         }

    //         // delete[] body.contents;
    //         closesocket(client);
    //     }

    // }
    
    // delete[] buffer;

    // closesocket(server);

    Server server(ip, port);
    server.run();

    WSACleanup();

    return 0;
}