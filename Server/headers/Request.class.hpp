#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>
#include "server.hpp"
#include <unistd.h>
#include <map>

typedef struct s_bodyPost
{
    std::string filename;
    std::string m_body;
} t_bodyPost;

typedef struct s_keyValue
{
    std::string key;
    std::string value;
} t_keyValue;

class Request
{
private:
    std::string m_boundary;
    std::vector<t_bodyPost> m_bodyPost;
    std::vector<t_keyValue> m_keyValue;
    std::string m_fileName;
    std::string m_betweenBoundary;
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::string m_firstRequestheader;
    std::string m_host;
    std::string m_hostSolo;
    std::string m_portSolo;
    std::string m_userAgent;
    std::string m_accept;
    std::string m_cookie;
    std::string m_fastCgi;
    std::string m_contentType;

    std::string m_contentLength;
    int m_countContentLength;
    int m_check;
    std::string m_body;
    std::string m_request;
    std::string m_mainRequest;
    std::map<int, std::string> m_requestMap;

public:
    Request();
    int concatRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i);
    int parseRequest(int socket);
    void getWords();
    int requestHeaders(int socket);
    void concatenation();
    void parsingRequestLine(std::string line);
    int parsingRequestGet(int socket);
    int parsingRequestPost(int socket, char *buffer);
    void parsingBetweenBoundary();
    void parseHost(std::string host);
    void uploadInFile(const char *path);
    void insetMapRequest(int socket);
    void init();
    int checkTheEndOfRequest(char *buffer);
    void parsingKeyValue();

    //  Accessors
    std::string getMethod() const;
    std::string getPath() const;
    std::string getVersion() const;
    std::string getFirstRequestHeader() const;
    std::string getHost() const;
    std::string getUserAgent() const;
    std::string getAccept() const;
    std::string getAcceptEncoding() const;
    std::string getAcceptLanguage() const;
    std::string getConnection() const;
    std::string getCookie() const;
    std::string getContentLength() const;
    std::string getHostSolo() const;
    std::string getPortSolo() const;
    std::string getFastCgi() const;
    std::string getBody() const;
    std::string getRequest() const;
    std::string getBoundary() const;
    std::string getFileName() const;
    std::string getBetweenBoundary() const;
    void setFastCgi(std::string fastCgi);
    void setRequest(std::string request);
    void setBody(std::string body);

    ~Request();
};

std::ostream &operator<<(std::ostream &out, Request &src);

#endif