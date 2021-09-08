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

class LocaTion;

class Server
{
private:
    int *m_socketFd;
    int m_maxFd;
    fd_set m_currentSocket;
    int m_newSocket;
    struct sockaddr_in m_address;
    int m_addrlen;
    Parse m_parse;
    Request m_request;
    Response m_response;

public:
    class NotFound
    {
    public:
        std::string notFoundBody() throw();
    };
    class Forbidden
    {
    public:
        std::string forbiddenBody() throw();
    };
    Server(Parse parse);
    int getSocketFd();
    void location(std::string &path);
    int locationContinued(int i, std::string &path);
    void acceptNewConnection(fd_set *readySocke);
    int checkForFileDescriptor(int current, int size);
    struct sockaddr_in getAddress();
    void initialiseStructure(int port, std::string ip);
    void manipulation();
    int checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path);
    void manageRequest(int socket);
    void debug(std::string str);
    std::string readingTheFile(char *filename);
    ~Server();
};

#endif