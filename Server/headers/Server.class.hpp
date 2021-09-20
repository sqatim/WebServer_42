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
#include "Request.class.hpp"
#include "Response.class.hpp"
#include "../../Parsing/webserv.hpp"

#define ROOT 1
#define REDIRECTION 2

class LocaTion;
// class Parse;

class Server
{
private:
    int m_socketFd;
    int m_maxFd;
    fd_set m_currentSocket;
    int m_newSocket;
    struct sockaddr_in m_address;
    int m_addrlen;
    // Parse m_parse;
    // Request m_request;
    // Response m_response;

public:
    Server(Parse parse, int &socket, std::vector<int> &servers, struct sockaddr_in &m_address);
    int whichLocation(Parse &parse, LocaTion location, std::string locationName, int socket);
    int getSocketFd();
    void initialiseStructure(int port, std::string ip, struct sockaddr_in &address);
    void debug(std::string str);
    ~Server();
};

#endif