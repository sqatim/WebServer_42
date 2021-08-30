#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>
#include "server.hpp"

class Request
{
private:
    std::string m_request;
    std::string m_body;
    std::string m_method;
    std::string m_path;
public:
    Request();
    // Request(std::string request);
    void parsingRequest();
    void getWords();
    // void getNextLine();
    //  Accessors
    std::string getRequest() const;
    std::string getBody() const;
    std::string getMethod() const;
    std::string getPath() const;
    void setRequest(std::string request);
    void setBody(std::string body);

    ~Request();
};

#endif