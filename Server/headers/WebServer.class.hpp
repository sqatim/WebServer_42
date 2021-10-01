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
    WebServer(WebServ &webServ);
    Server setServer(Parse &parse);
    void run();
    void acceptNewConnection();
    void manageRequest(int socket, int check, int request);
    int checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path);
    std::string readingTheFile(char *filename);
    void getMethod(int socket);
    void postMethod(int socket);
    void deleteMethod(int socket);
    void deleteMethodComparaison(int socket, size_t &i);
    void postMethodComparaison(int socket, size_t &i, std::string &locationName, int &check);
    int location(int socket);
    int CheckingForCgi(int socket);
    int checkingForTheRightLocation(LocaTion &location, std::string &url, int &check, int socket);
    int whichLocation(LocaTion location);
    int appendLocation(LocaTion location);
    void checkingClient();
    void choosingTheRightServer(std::string &requestHost, int &check);
    int theRightServerName(std::string &requestHost, Parse &parse, std::string &host, size_t &j);
    std::vector<int> getServer() const;
    int getMaxSocket() const;
    void debug(std::string str);
    class NotFound
    {
    private:
        Parse m_parse;
        std::string m_fileName;

    public:
        NotFound(){};
        NotFound(Parse parse, std::string fileName) : m_parse(parse), m_fileName(fileName){};
        Parse getParse() { return m_parse; };
        std::string getFileName() { return m_fileName; };
        std::string notFoundBody() throw();
    };
    class Forbidden
    {
    private:
        Parse m_parse;
        std::string m_fileName;

    public:
        Forbidden(){};
        Forbidden(Parse parse, std::string fileName) : m_parse(parse), m_fileName(fileName){};
        Parse getParse() { return m_parse; };
        std::string getFileName() { return m_fileName; };
        std::string forbiddenBody() throw();
    };
    class TooLarge
    {
    private:
        Parse m_parse;
        std::string m_fileName;

    public:
        TooLarge(){};
        TooLarge(Parse parse, std::string fileName) : m_parse(parse), m_fileName(fileName){};
        Parse getParse() { return m_parse; };
        std::string getFileName() { return m_fileName; };
        std::string toLargeBody() throw();
    };
    class MethodNotAllowed
    {
    private:
        Parse m_parse;
        std::string m_fileName;

    public:
        MethodNotAllowed(){};
        MethodNotAllowed(Parse parse, std::string fileName) : m_parse(parse), m_fileName(fileName){};
        Parse getParse() { return m_parse; };
        std::string getFileName() { return m_fileName; };
        std::string methodNotAllowed() throw();
    };
    ~WebServer();
};

#endif