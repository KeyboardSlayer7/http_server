#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

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
};

#endif // SERVER_H