#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include <iostream>
#include <sstream>
#include "../../Parsing/parse.hpp"
#include "server.hpp"
#include <unistd.h>
#include <dirent.h>

#define ROOT 1
#define REDIRECT 2

class Response
{
private:
    std::string m_version;
    std::string m_status;
    std::string m_contentType;
    std::string m_location;
    std::string m_contentLength;
    std::string m_response;
    std::string m_header;
    std::string m_body;
    std::vector<std::string> m_setCookies;
    int m_type;

public:
    Response(/* args */);
    void initResponse();
    void contentHeader(std::string status, std::string type1, std::string type2, std::string body);
    void defaultBody();
    void notFoundBody(Parse parse, std::string root);
    void forbiddenBody(Parse parse, std::string root);
    void toLargeBody(Parse parse, std::string root);
    void badRequestBody(Parse parse, std::string root);
    void methodNotAllowedBody(Parse parse, std::string root);
    void fileDeleted();
    void fileUploaded();
    int checkLocation(LocaTion location);
    void redirectHeader(std::string status, std::string location);
    void redirectHeaderToPath(std::string status, std::string host, std::string url);
    void simpleLocation();
    std::string autoIndexBody(const char *fileName, const char *url);
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
    void setCookies(std::vector<std::string> cookies);

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