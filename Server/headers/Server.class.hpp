#ifndef SERVER_CLASS_HPP
#define SERVER_CLASS_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cctype>
#include <cstring>
#include <fstream>
// 7ta nshuf blanhum man ba3d
#include <unistd.h>
#include <fcntl.h>
#include "server.hpp"
#include "../../Parsing/parse.hpp"

// #define PORT 5000

class Server
{
private:
    t_content m_content;
    int *m_socketFd;
    int m_maxFd;
    fd_set m_currentSocket;
    int m_newSocket;
    struct sockaddr_in m_address;
    int m_addrlen;
    t_response m_response;

public:
    // std::string responseConcatenation(std::string status, int length, std::string type[2], std::string body);
    // Server(int port);
    Server(Parse parse);
    int getSocketFd();
    int checkForFileDescriptor(int current, int size);
    struct sockaddr_in getAddress();
    void initialiseStructure(int port, std::string host);
    void manipulation(Parse parse);
    void manageRequest(std::string word, Parse parse, int socket);
    ~Server();
};

#endif