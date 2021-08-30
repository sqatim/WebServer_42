#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>

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
    void getWords(char *str,  int nLine, int nWord);
    // void getNextLine();
    //  Accessors
    std::string getRequest() const;
    std::string getBody() const;
    void setRequest(std::string request);
    void setBody(std::string body);

    ~Request();
};

#endif