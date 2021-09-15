#ifndef WEBSERVER_CLASS_HPP
#define WEBSERVER_CLASS_HPP

#include <vector>
#include <iostream>
#include "Server.class.hpp"

class Parse;

class WebServer
{
private:
    std::vector<int> m_server;
    // int m_maxSocketPerServer;
    int m_maxSocket;
    fd_set m_writeSocket;
    fd_set m_currentSocket;
    int m_maxFd;
    std::vector<int> m_clientSocket;
    struct sockaddr_in m_address;
    int m_addrlen;
    Response m_response;
    Request m_request;
    WebServ m_webServ;
    Parse m_parse;

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
    WebServer(WebServ &webServ);
    Server setServer(Parse &parse);
    void run();
    void acceptNewConnection();
    void manageRequest(int socket);
    int checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path);
    std::string readingTheFile(char *filename);
    void getMethod(int socket);
    int location(int socket);
    int whichLocation(Parse &parse, LocaTion location, std::string locationName, int socket);
    int appendLocation(LocaTion location, int socket);

    std::vector<int> getServer() const;
    int getMaxSocket() const;
    ~WebServer();
    void debug(std::string str);
};

#endif