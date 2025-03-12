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

    const char* ip = "127.0.0.1";
    int port = 42069;

    Server server(ip, port);
    server.run();

    WSACleanup();

    return 0;
}