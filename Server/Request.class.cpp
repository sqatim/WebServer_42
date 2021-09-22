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
    m_body = "";
    m_request = "";
    m_mainRequest = "";
    m_cookie = "";
}

Request::Request() : m_boundary("11111111"), m_fileName(""), m_betweenBoundary(""),
                     m_method(""), m_path(""), m_version(""), m_firstRequestheader(""), m_host(""),
                     m_userAgent(""), m_accept(""), m_body(""), m_request(""), m_mainRequest(""),
                     m_cookie("")
{
}

void Request::requestHeaders()
{
    std::istringstream stringStream(m_mainRequest);
    std::string line;

    while (std::getline(stringStream, line, '\n'))
    {
        if (m_host == "" && line.compare(0, 6, "Host: ") == 0)
            m_host = line;
        else if (m_userAgent == "" && line.compare(0, 12, "User-Agent: ") == 0)
            m_userAgent = line;
        else if (m_accept == "" && line.compare(0, 8, "Accept: ") == 0)
            m_accept = line;
        else if (m_cookie == "" && line.compare(0, 8, "Cookie: ") == 0)
            m_cookie = line;
    }
}

void Request::concatenation()
{
    m_request = m_firstRequestheader + "\r\n";
    m_request += m_host + "\r\n";
    m_request += m_userAgent + "\r\n";
    m_request += m_accept + "\r\n";
    m_request += m_cookie + "\r\n";
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

void Request::parsingRequestLine(std::string buffer)
{
    std::string word;
    std::string path;
    std::istringstream stringStream;
    this->m_firstRequestheader = buffer;
    stringStream.str(this->m_firstRequestheader);
    getline(stringStream, word, ' ');
    this->m_method = word;
    getline(stringStream, word, ' ');
    path = word;
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
    return (result);
}

void Request::uploadInFile(const char *path)
{
    std::string file = path;
    file.insert(file.length(), m_fileName);
    std::ofstream myWriteFile(file);
    // std::cout << "file name : " << file << std::endl;
    // std::cout << m_body << std::endl;
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
                // std::cout << line << std::endl;
                m_body += line;
                std::getline(stringStream, line, '\n');
                if (line.find(m_boundary) == std::string::npos)
                    m_body += '\n';
            }
        }
    }
}

void Request::parsingRequestPost(int socket, char **buffer)
{
    std::string line;
    std::string boundry;
    int check = 0;
    size_t i;

    // std::cout << "************* POST *************" << std::endl;
    while (get_next_line(socket, &(*buffer)) > 0)
    {
        line = *buffer;
        // std::cout << *buffer << std::endl;
        this->m_mainRequest += *buffer;
        this->m_mainRequest += "\n";
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
                // std::cout << "line : " << line << std::endl;
                m_betweenBoundary += line;
                check = 3;
                break;
            }
            m_betweenBoundary += line + '\n';
            check = 2;
        }
        delete[](*buffer);
    }
    this->requestHeaders();
    parsingBetweenBoundary();
    this->concatenation();
    // std::cout << m_request << std::endl;
    // std::cout << "*************  *************" << std::endl;
}

void Request::parsingRequestGet(int socket, char **buffer)
{
    while (get_next_line(socket, &(*buffer)) > 0)
    {
        std::cout << *buffer << std::endl;
        this->m_mainRequest += *buffer;
        this->m_mainRequest += "\n";
        delete[](*buffer);
    }
    this->requestHeaders();
    // std::cout << "************* GET *************" << std::endl;
    this->concatenation();
    // std::cout << m_request << std::endl;
    // std::cout << "*************  *************" << std::endl;
}
int Request::parsingRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i)
{
    char *buffer;
    int result;
    if ((result = get_next_line(socket, &buffer)) == 0)
    {
        std::cout << "disconnected 0" << std::endl;
        close(socket);
        clientSocket.erase(clientSocket.begin() + i);
        FD_CLR(socket, &(*readySockets));
        FD_CLR(socket, &(*writeSockets));
        // init();
        return (0);
    }
    else if (result == -1)
        return (0);
    else
    {
        std::cout << buffer << std::endl;
        this->m_mainRequest += buffer;
        this->m_mainRequest += "\n";
        if (m_firstRequestheader == "")
            this->parsingRequestLine(buffer);
        delete[] buffer;
        if (m_method == "GET" || m_method == "DELETE")
            parsingRequestGet(socket, &buffer);
        else if (m_method == "POST")
            parsingRequestPost(socket, &buffer);
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

std::string Request::getCookie() const
{
    return (this->m_cookie);
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