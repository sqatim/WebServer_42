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
    int whichLocation(Parse& parse, LocaTion location ,std::string locationName, int socket);
    int getSocketFd();
    void getMethod(int socket);
    int location(int socket);
    int appendLocation(LocaTion location, int socket);
    // int locationContinuedtest(int i, std::string &path, std::string location);
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