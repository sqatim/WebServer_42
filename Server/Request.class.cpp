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
    getline(stringStream, line, ' ');
    // array = ft_split(line, ' ');
    this->m_method = line;
    getline(stringStream, line, ' ');
    // std::cout << "lbab ahlh bab" << std::endl;
    path = line;
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
    // for (int i = 0; array[i]; i++)
    //     delete array[i];
    // delete[] array;
}
int Request::parsingRequest(int socket, fd_set *readySockets,fd_set *writeSockets, std::vector<int> &clientSocket, int i)
{
    char *buffer;
    // char buffer[3000] = {0};
    int counter;
    int result;

    counter = 0;
    // if ((result = read(socket, buffer, 3000)) == 0)
    if (get_next_line(socket, &buffer) == 0)
    {
        std::cout << "disconnected 0" << std::endl;
        close(socket);
        clientSocket.erase(clientSocket.begin() + i);
        FD_CLR(socket, &(*readySockets));
        FD_CLR(socket, &(*writeSockets));
        return (0);
    }
    else if (result == -1)
    {
        //     std::cout << "disconnected -1" << std::endl;
        //     close(socket);
        //     FD_CLR(socket, &(*readySockets));
        //     // exit(0);
        return (0);
    }
    else
    {
        // std::cout << "oussama " << std::endl;
        // buffer[result] = '\0';
        // std::cout << "*****************************" << std::endl;
        // std::cout << buffer << std::endl;
        this->requestHeaders(counter, buffer);
        delete[] buffer;
        counter++;
        while (get_next_line(socket, &buffer) > 0)
        {
            // std::cout << "shalam shamir" << std::endl;
            // std::cout << buffer << std::endl;
            this->requestHeaders(counter, buffer);
            counter++;
            if (buffer[0] == '\0')
                break;
            delete[] buffer;
        }
        // std::cout << "*****************************" << std::endl;
        this->concatenation();
        this->parsingRequestLine();
        // std::cout << this->m_request;
        // FD_CLR(socket, &(*readySockets));
        return (1);
    }
}

std::string Request::getVersion() const
{
    return (this->m_version);
}
std::string Request::getFirstRequestHeader() const
{
    return (this->m_firstRequestheader);
}

std::string Request::getUserAgent() const
{
    return (this->m_userAgent);
}
std::string Request::getAccept() const
{
    return (this->m_accept);
}
std::string Request::getAcceptEncoding() const
{
    return (this->m_acceptEncoding);
}
std::string Request::getAcceptLanguage() const
{
    return (this->m_acceptLanguage);
}
std::string Request::getConnection() const
{
    return (this->m_connection);
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

std::ostream &operator<<(std::ostream &out, Request &src)
{
    out << src.getRequest() << std::endl;
    return (out);
}