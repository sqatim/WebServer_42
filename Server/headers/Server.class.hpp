#ifndef SERVER_CLASS_HPP
#define SERVER_CLASS_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <fstream>
// 7ta nshuf blanhum man ba3d
#include <unistd.h>
#include <fcntl.h>
#include "server.hpp"
#include "../../Parsing/parse.hpp"

#define PORT 5000

class Server
{
private:
    int m_socketFd;
    int m_newSocket;
    struct sockaddr_in m_address;
    int m_addrlen;
    t_response m_response;

public:
    // std::string responseConcatenation(std::string status, int length, std::string type[2], std::string body);
    Server(/* args */);
    int getSocketFd();
    struct sockaddr_in getAddress();
    void initialiseStructure(void);
    void manipulation();
    ~Server();
};

#endif