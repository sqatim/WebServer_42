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
    }
}

void Request::concatenation()
{
    m_request = m_firstRequestheader + "\r\n";
    m_request += m_host + "\r\n";
    m_request += m_userAgent + "\r\n";
    m_request += m_accept + "\r\n";
    m_request += m_acceptEncoding + "\r\n";
    m_request += m_acceptLanguage + "\r\n";
    m_request += m_connection + "\r\n";
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

void Request::parsingRequestLine()
{
    std::string line;
    std::string path;
    std::istringstream stringStream;
    char **array;
    stringStream.str(this->m_request);
    getline(stringStream, line);
    array = ft_split(line, ' ');
    this->m_method = toString(array[0]);
    path = toString(array[1]);
    for (int j = path.length() - 1; (path[j] == '/' && j != 0); j--)
    {
        if (path[j - 1] != '/')
            break;
        path[j] = '\0';
    }
    // for (int i = path.length() - 1; (path.c_str()[i] == '/' && i != 0); i--)
    // path[i] = '\0';
    // slash(&path);
    this->m_path = path.c_str();
    for (int i = 0; array[i]; i++)
        delete array[i];
    delete[] array;
}
int Request::parsingRequest(int socket, fd_set *readySockets)
{
    char *buffer;
    // char buffer[3000] = {0};
    int counter;

    counter = 0;
    // if (read(socket, buffer, 3000) == 0)
    if (get_next_line(socket, &buffer) == 0)
    {
        std::cout << "disconnected" << std::endl;
        close(socket);
        FD_CLR(socket, &(*readySockets));
        return (0);
    }
    else
    {
        std::cout << "*****************************" << std::endl;
        this->requestHeaders(counter, buffer);
        std::cout << buffer << std::endl;
        delete[] buffer;
        counter++;
        while (get_next_line(socket, &buffer) > 0)
        {
            std::cout << buffer << std::endl;
            this->requestHeaders(counter, buffer);
            counter++;
            if (buffer[0] == '\0')
                break;
            delete[] buffer;
        }
        std::cout << "*****************************" << std::endl;
        this->concatenation();
        this->parsingRequestLine();
        return (1);
    }
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

std::string Request::getHost(void) const
{
    return this->m_host;
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