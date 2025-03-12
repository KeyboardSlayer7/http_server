#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include "nlohmann/json.hpp"

#include "http_parser.h"

using json = nlohmann::json;

struct Content
{
    std::string type;
    std::vector<char> data;
};

class Server
{
public:
    Server(const char* host, int port);
    Server(const char* host, const char* port);
    ~Server();

    void run();
private:
    SOCKADDR_IN _address;
    SOCKET _socket;
    std::vector<char> _buffer;
    bool _running;
    
    json _content_types;

    std::string createResponse(Http& http, Content& content);
};

#endif // SERVER_H