#include "Request.class.hpp"
#include <sstream>

Request::Request() : m_request(""), m_body("")
{
}

int ft_strlen(char **str)
{
    int i;

    i = 0;
    while (str[i] != 0)
        i++;
    return (i);
}

std::string toString(char *string)
{
    std::string word(string);
    return (word);
}

void Request::getWords()
{
}

void Request::parsingRequest()
{
    std::string line;
    std::istringstream stringStream;
    char **array;
    stringStream.str(this->m_request);
    getline(stringStream, line);
    array = ft_split(line, ' ');
    this->m_method = toString(array[0]);
    this->m_path = toString(array[1]);
    for (int i = 0; array[i]; i++)
        delete array[i];
    delete[] array;
}

std::string Request::getRequest(void) const
{
    return this->m_request;
}

std::string Request::getBody(void) const
{
    return this->m_body;
}

std::string Request::getMethod(void) const
{
    return this->m_method;
}

std::string Request::getPath(void) const
{
    return this->m_path;
}

void Request::setRequest(std::string request)
{
    this->m_request = request;
}

void Request::setBody(std::string body)
{
    this->m_body = body;
}

Request::~Request()
{
}