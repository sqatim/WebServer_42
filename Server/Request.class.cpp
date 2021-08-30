#include "Request.class.hpp"

Request::Request() : m_request(""), m_body("")
{
}

#include "Server.class.hpp"

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

std::string parseString(std::istringstream &stringStream, int nLine, int nWord)
{
    char **tab;
    std::string line;
    std::string word;

    for (int number = 0; number <= nLine; number++)
        getline(stringStream, line);
    tab = ft_split(line, ' ');
    if (nWord >= ft_strlen(tab))
        return ("");
    word = toString(tab[nWord]);
    for (int i = 0; tab[i]; i++)
        delete tab[i];
    delete[] tab;
    return (word);
}
std::string Request::getWords(char *str, int nLine, int nWord)
{
    int r;
    std::string line;
    std::istringstream stringStream;
    char **array;
    std::string fileStr(str);
    stringStream.str(fileStr);
    getline(stringStream, line);
    array = ft_split(line, ' ');
    this->m_request = toString(array[0]);
    this->m_path = toString(array[1]);
    return (parseString(stringStream, nLine, nWord));
}

void Request::parsingRequest()
{
}

std::string Request::getRequest(void) const
{
    return this->m_request;
}

std::string Request::getBody(void) const
{
    return this->m_body;
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