#ifndef RESPONSE_CLASS_HPP
#define RESPONSE_CLASS_HPP

#include <iostream>

class Response
{
private:
    std::string m_version;
    std::string m_status;
    std::string m_contentType;
    std::string m_contentLength;
    std::string m_connection;
    std::string m_response;
    std::string m_header;
    std::string m_body;

public:
    Response(/* args */);
    void initResponse();
    void contentHeader(std::string status, std::string type1, std::string type2, std::string body);
    void defaultBody();
    void notFoundBody();
    void forbiddenBody();
    // Setters
    void setVersion(std::string version);
    void setStatus(std::string status);
    void setContentType(std::string type1, std::string type2);
    void setContentLength(std::string length);
    void setBody(std::string status);
    void setHeader(std::string header);
    void setResponse(std::string response);
    void setHeader();
    void setResponse();

    // Getters
    std::string getStatus() const;
    std::string getBody() const;
    std::string getResponse() const;

    ~Response();
};

#endif