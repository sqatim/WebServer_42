#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include <iostream>
#include <sstream>
#include "../../Parsing/parse.hpp"
#include <unistd.h>
#include <dirent.h>

#define REDIRECT 1

// class LocaTion;
class Response
{
private:
    std::string m_version;
    std::string m_status;
    std::string m_contentType;
    std::string m_location;
    std::string m_contentLength;
    std::string m_connection;
    std::string m_response;
    std::string m_header;
    std::string m_body;
    int m_type;

public:
    Response(/* args */);
    void initResponse();
    void contentHeader(std::string status, std::string type1, std::string type2, std::string body);
    void defaultBody();
    void notFoundBody();
    void forbiddenBody();
    int checkLocation(LocaTion location);
    void redirectHeader(int socket, std::string status, std::string location);
    void redirectHeaderToPath(int socket, std::string status, std::string host,std::string url);
    void simpleLocation();
    std::string autoIndexBody(const char* fileName, const char *url);
    void sendResponse(int socket);
    // Setters
    void setVersion(std::string version);
    void setStatus(std::string status);
    void setContentType(std::string type1, std::string type2);
    void setLocation(std::string location);
    void setContentLength(std::string length);
    void setBody(std::string status);
    void setHeader(std::string header);
    void setResponse(std::string response);
    void setHeader();
    void setResponse();
    void setType(int type);
    void statusIndication(std::string status);

    // Getters
    std::string getLocation() const;
    std::string getStatus() const;
    std::string getHeader() const;
    std::string getBody() const;
    std::string getResponse() const;
    int getType() const;

    ~Response();
};

#endif