#include "Request.class.hpp"
#include <sstream>

void Request::init()
{
    m_boundary = "11111111";
    m_fileName = "";
    m_betweenBoundary = "";
    m_method = "";
    m_path = "";
    m_version = "";
    m_firstRequestheader = "";
    m_host = "";
    m_userAgent = "";
    m_accept = "";
    m_acceptEncoding = "";
    m_acceptLanguage = "";
    m_connection = "";
    m_body = "";
    m_request = "";
}

Request::Request() : m_request(""), m_body(""), m_fileName(""), m_boundary("111111")
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
    stringStream.str(this->m_firstRequestheader);
    getline(stringStream, line, ' ');
    // array = ft_split(line, ' ');
    this->m_method = line;
    getline(stringStream, line, ' ');
    path = line;
    for (int j = path.length() - 1; (path[j] == '/' && j != 0); j--)
    {
        if (path[j - 1] != '/')
            break;
        path[j] = '\0';
    }
    this->m_path = path.c_str();
}

std::string justBoundary(std::string host)
{
    std::stringstream stringStream(host);
    std::string result;
    std::getline(stringStream, result, '=');
    std::getline(stringStream, result, '=');
    // std::cout << result << std::endl;
    return (result);
}

void Request::uploadInFile()
{
    std::string path = "/Users/sqatim/Desktop/testNginx/" + m_fileName;
    std::cout << path.c_str() << std::endl;
    std::ofstream myWriteFile(path);
    myWriteFile << m_body;
    myWriteFile.close();
}

void Request::parsingBetweenBoundary()
{
    std::stringstream stringStream(m_betweenBoundary);
    std::string line;
    size_t filename;
    // std::cout << m_betweenBoundary << std::endl;
    while (std::getline(stringStream, line, '\n'))
    {
        if (m_fileName == "" && (filename = line.find("filename")) != std::string::npos)
        {
            while (line[filename] != '\"')
                filename++;
            filename++;
            for (; line[filename] != '\"' && line[filename + 1]; filename++)
            {
                m_fileName += line[filename];
            }
            m_fileName += '\0';
            std::getline(stringStream, line, '\n');
            std::getline(stringStream, line, '\n');
            std::getline(stringStream, line, '\n');
            while (line.find(m_boundary) == std::string::npos)
            {
                m_body += line;
                std::getline(stringStream, line, '\n');
                if (line.find(m_boundary) == std::string::npos)
                    m_body += '\n';
            }
            uploadInFile();
            // std::cout << m_body << std::endl;
        }
    }
}

void Request::parsingRequestPost(int socket, char **buffer, int counter)
{
    std::string line;
    std::string boundry;
    int check = 0;
    size_t i;

    while (get_next_line(socket, &(*buffer)) > 0)
    {
        std::cout << *buffer << std::endl;
        line = *buffer;
        if (check == 0 && ((i = line.find("boundary")) != std::string::npos))
        {
            boundry = &line[i];
            m_boundary = justBoundary(boundry);
            check++;
        }
        else if (check == 2 || line.find(m_boundary) != std::string::npos)
        {
            if (check == 2 && line.find(m_boundary) != std::string::npos)
            {
                m_betweenBoundary += line;
                check = 3;
                break;
            }
            m_betweenBoundary += line + '\n';
            check = 2;
        }
        this->requestHeaders(counter, *buffer);
        counter++;
        delete[](*buffer);
    }
    parsingBetweenBoundary();
    this->concatenation();
}

void Request::parsingRequestGet(int socket, char **buffer, int counter)
{
    while (get_next_line(socket, &(*buffer)) > 0)
    {
        std::cout << *buffer << std::endl;
        this->requestHeaders(counter, *buffer);
        counter++;
        // if ((*buffer)[0] == '\0')
        // {
        //     if (m_method == "GET")
        //         break;
        // }
        delete[](*buffer);
    }
    this->concatenation();
    // std::cout << this->m_request << std::endl;
}
int Request::parsingRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i)
{
    char *buffer;
    // char buffer[3000] = {0};
    int counter;
    int result;

    counter = 0;
    // if ((result = read(socket, buffer, 3000)) == 0)
    if ((result = get_next_line(socket, &buffer)) == 0)
    {
        std::cout << "disconnected 0" << std::endl;
        close(socket);
        clientSocket.erase(clientSocket.begin() + i);
        FD_CLR(socket, &(*readySockets));
        FD_CLR(socket, &(*writeSockets));
        return (0);
    }
    else if (result == -1)
        return (0);
    else
    {
        // buffer[result] = '\0';
        // std::cout << "*****************************" << std::endl;
        std::cout << buffer << std::endl;
        this->requestHeaders(counter, buffer);
        this->parsingRequestLine();
        delete[] buffer;
        counter++;
        if (m_method == "GET")
            parsingRequestGet(socket, &buffer, counter);
        else if (m_method == "POST")
            parsingRequestPost(socket, &buffer, counter);
        // std::cout << "*****************************" << std::endl;
        // this->concatenation();
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

std::string Request::getBoundary() const
{
    return (this->m_boundary);
}

std::string Request::getFileName() const
{
    return (this->m_fileName);
}

std::string Request::getBetweenBoundary() const
{
    return (this->m_betweenBoundary);
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