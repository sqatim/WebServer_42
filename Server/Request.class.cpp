#include "Request.class.hpp"
#include <sstream>

Request::Request() : m_request(""), m_body("")
{
    m_tab[0] = &m_firstRequestheader;
    m_tab[1] = &m_host;
    m_tab[2] = &m_userAgent;
    m_tab[3] = &m_accept;
    m_tab[4] = &m_acceptEncoding;
    m_tab[5] = &m_acceptLanguage;
    m_tab[6] = &m_connection;
}

void Request::requestHeaders(int i, char *str)
{
    if (i < 7)
    {
        *m_tab[i] = str;
        // std::cout << "tab[" << i << "] " << *m_tab[i] << std::endl;
    }
    std::cout << "i ==> " << i << std::endl;
}

void Request::concatenation()
{
    m_request = m_firstRequestheader;
    m_request += m_host;
    m_request += m_userAgent;
    m_request += m_accept;
    m_request += m_acceptEncoding;
    m_request += m_acceptLanguage;
    m_request += m_connection;
    std::cout << "**********************************" << std::endl;
    std::cout << "ash fiiha ==> " << m_request << std::endl;
    std::cout << "**********************************" << std::endl;
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
    // if (this->m_request[0] != '\r')
    // {
    // std::cout << "============================" << std::endl;
    // for (int i = 0; this->m_request.c_str()[i]; i++)
    // {
    //     std::cout << "i: " << i;
    // }
    // std::cout << "============================" << std::endl;
    stringStream.str(this->m_request);
    getline(stringStream, line);
    array = ft_split(line, ' ');
    this->m_method = toString(array[0]);
    this->m_path = toString(array[1]);
    for (int i = 0; array[i]; i++)
        delete array[i];
    delete[] array;
    // }
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