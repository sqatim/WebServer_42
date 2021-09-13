#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>
#include "server.hpp"
#include <unistd.h>

class Request
{
private:
    std::string *m_tab[7];
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::string m_firstRequestheader;
    std::string m_host;
    std::string m_userAgent;
    std::string m_accept;
    std::string m_acceptEncoding;
    std::string m_acceptLanguage;
    std::string m_connection;
    std::string m_body;
    std::string m_request;

public:
    Request();
    int parsingRequest(int socket, fd_set *readySockets);
    void getWords();
    void requestHeaders(int i, char *str);
    void concatenation();
    void parsingRequestLine();

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
    std::string getBody() const;
    std::string getRequest() const;
    void setRequest(std::string request);
    void setBody(std::string body);

    ~Request();
};

std::ostream &operator<<(std::ostream &out, Request &src);


#endif