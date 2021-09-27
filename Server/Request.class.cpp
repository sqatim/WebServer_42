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
    m_hostSolo = "";
    m_portSolo = "";
    m_userAgent = "";
    m_accept = "";
    m_body = "";
    m_request = "";
    m_mainRequest = "";
    m_cookie = "";
    m_contentLength = "";
    m_fastCgi = "";
    m_countContentLength = 0;
    m_check = 0;
}

Request::Request() : m_boundary("11111111"), m_fileName(""), m_betweenBoundary(""),
                     m_method(""), m_path(""), m_version(""), m_firstRequestheader(""), m_host(""),
                     m_userAgent(""), m_accept(""), m_body(""), m_request(""), m_mainRequest(""),
                     m_cookie(""), m_contentLength(""), m_portSolo(""), m_hostSolo(""), m_fastCgi(""),
                     m_countContentLength(0), m_check(0)
{
}

void Request::parseHost(std::string host)
{
    std::stringstream stringStream(host);
    std::getline(stringStream, m_hostSolo, ' ');
    std::getline(stringStream, m_portSolo, ' ');
}

int Request::requestHeaders(int socket)
{
    std::istringstream stringStream(m_requestMap[socket]);
    std::string line;
    std::string ss = "";
    std::string host;
    int i = 0;

    while (std::getline(stringStream, line, '\r'))
        ss += line;
    std::istringstream file(ss);
    line = "";
    while (std::getline(file, line, '\n'))
    {
        // std::cout << line << std::endl;
        if (m_host == "" && line.compare(0, 6, "Host: ") == 0)
        {
            m_host = line;
            host = justHost(line);
        }
        else if (m_boundary == "11111111" && (i = line.find("boundary=") != std::string::npos))
        {
            i = line.find("boundary=");
            m_boundary = &line[i + 9];
        }
        else if (m_userAgent == "" && line.compare(0, 12, "User-Agent: ") == 0)
            m_userAgent = line;
        else if (m_accept == "" && line.compare(0, 8, "Accept: ") == 0)
            m_accept = line;
        else if (m_cookie == "" && line.compare(0, 8, "Cookie: ") == 0)
            m_cookie = line;
        else if (m_contentLength == "" && line.compare(0, 16, "Content-Length: ") == 0)
            m_contentLength = line;
    }
    if (m_method == "POST")
    {
        parsingBetweenBoundary();
    }
    this->concatenation();
    return (0);
}

void Request::concatenation()
{
    m_request = m_firstRequestheader + "\r\n";
    m_request += m_host + "\r\n";
    m_request += m_userAgent + "\r\n";
    m_request += m_accept + "\r\n";
    m_request += m_cookie + "\r\n";
    m_request += m_contentLength + "\r\n";
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
    myWriteFile << m_body;
    myWriteFile.close();
}

void Request::parsingBetweenBoundary()
{
    std::stringstream countBoundary(m_body);
    std::string buffer = m_body;
    std::stringstream stringStream(buffer);
    std::string line;
    size_t filename;
    // std::cout << m_betweenBoundary << std::endl;
    int counter = 0;
    int i = 0;
    int l = 0;
    int check = 0;
    // while()
    // std::cout << m_body << std::endl;
    // exit(0);
    while (std::getline(countBoundary, line, '\r'))
    {
        if (line.find(m_boundary) != std::string::npos)
            counter++;
    }
    line = "";
    while (i < counter - 1)
    {
        if (m_bodyPost.size() == 0)
        {
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            m_bodyPost.push_back({"", ""});
            filename = line.find("filename");
            line = &line[filename + 10];
            l = 0;
            for (; line[l] != '\"' && line[l + 1]; l++)
                m_bodyPost[0].filename += line[l];
            l = 0;
            while (std::getline(stringStream, line, '\r') && l < 2)
                l++;
            line = &line[1];
            if (line.c_str()[line.length() - 1] == '\n')
                line[line.length() - 1] = '\0';
            m_bodyPost[0].m_body = line;
            check = 1;
        }
        else
        {
            m_bodyPost.push_back({"", ""});
            line = "";
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            filename = line.find("filename");
            line = &line[filename + 10];
            l = 0;
            for (; line[l] != '\"' && line[l + 1]; l++)
                m_bodyPost[i].filename += line[l];
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            line = &line[1];
            if (line.c_str()[line.length() - 1] == '\n')
                line[line.length() - 1] = '\0';
            m_bodyPost[i].m_body = line;
        }
        i++;
    }
    // std::cout << line << std::endl;

    // std::getline(stringStream, line, '\r');
    // while (std::getline(stringStream, line, '\n') && counter < 4)
    // {
    //     std::cout << line << std::endl;
    //     counter++;
    // }
    // while (std::getline(stringStream, line, '\n'))
    // {
    //     if (m_fileName == "" && (filename = line.find("filename")) != std::string::npos)
    //     {
    //         while (line[filename] != '\"')
    //             filename++;
    //         filename++;
    //         for (; line[filename] != '\"' && line[filename + 1]; filename++)
    //         {
    //             m_fileName += line[filename];
    //         }
    //         m_fileName += '\0';
    //         std::getline(stringStream, line, '\n');
    //         std::getline(stringStream, line, '\n');
    //         std::getline(stringStream, line, '\n');
    //         while (line.find(m_boundary) == std::string::npos)
    //         {
    //             // std::cout << line << std::endl;
    //             m_body += line;
    //             std::getline(stringStream, line, '\n');
    //             if (line.find(m_boundary) == std::string::npos)
    //                 m_body += '\n';
    //         }
    //     }
    // }
}

int Request::parsingRequestPost(int socket, char *buffer)
{
    std::stringstream stringStream(buffer);
    std::stringstream string;
    std::string removeBackSlashR;
    std::string line(buffer);
    std::string boundry;
    std::string body;
    int check = 0;
    size_t i = 0;
    size_t j = 0;

    // std::cout << line << std::endl;
    // exit(0);
    if (m_check == 0)
    {
        if ((i = line.find("Content-Length: ")) != std::string::npos)
        {
            j = i;
            while (line[i + 16] != '\r')
            {
                m_contentLength += line[i + 16];
                if (line[i + 17] == '\r')
                {
                    line[i + 17] = '\0';
                    i = i + 19;
                    break;
                }
                i++;
            }
            m_check = 1;
        }
    }
    if (m_check == 1)
    {
        body = &line[i];
        int i = 0;
        while (m_countContentLength < std::atoi(m_contentLength.c_str()) && m_countContentLength < body.length())
        {
            m_body += body[i];
            i++;
            m_countContentLength++;
        }
        if (m_countContentLength == std::atoi(m_contentLength.c_str()))
            return (-2);
    }
    return (1);
}

int Request::parsingRequestGet(int socket)
{
    int result;
    result = this->requestHeaders(socket);
    this->concatenation();
    if (result == 1)
        return (1);
    return (0);
}

void Request::insetMapRequest(int socket)
{
    m_requestMap.insert({socket, ""});
}

int Request::parseRequest(int socket)
{

    this->requestHeaders(socket);
    this->concatenation();
    return (1);
}

int Request::checkTheEndOfRequest(char *buffer)
{
    std::stringstream stringStream(buffer);
    std::stringstream stream;
    std::string line;
    std::string request = "";
    size_t i = 0;
    std::string body;
    if (m_method == "GET" || m_method == "DELETE")
    {
        while (std::getline(stringStream, line, '\r'))
            request += line;
        line = "";
        while (std::getline(stream, line, '\n'))
        {
            if (line[0] == '\r' || line[0] == '\0')
                return (1);
        }
    }
    else if (m_method == "POST")
    {
        line = buffer;
        // std::cout << buffer << std::endl;
        if (m_check == 0)
        {
            if ((i = line.find("Content-Length: ")) != std::string::npos)
            {
                while (line[i + 16] != '\r')
                {
                    m_contentLength += line[i + 16];
                    if (line[i + 17] == '\r')
                    {
                        line[i + 17] = '\0';
                        i = i + 21;
                        break;
                    }
                    i++;
                }
                m_check = 1;
            }
        }
        if (m_check == 1)
        {
            body = &line[i];
            // std::cout << body << std::endl;
            i = 0;
            while (m_countContentLength < std::atoi(m_contentLength.c_str()) && i < body.length())
            {
                m_body += body[i];
                i++;
                m_countContentLength++;
            }
            if (m_countContentLength == std::atoi(m_contentLength.c_str()))
                return (1);
        }
    }
    return (0);
}
int Request::concatRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i)
{
    char buffer[2500];
    int result;
    std::istringstream stringStream;
    std::istringstream string;
    std::string removeBackSlashR = "";
    std::string line;

    if ((result = read(socket, buffer, 2500)) > 0)
    {
        buffer[result] = '\0';
        std::cout << buffer << std::endl;
        m_requestMap[socket] += buffer;
        if (m_firstRequestheader == "")
            this->parsingRequestLine(buffer);
        if (m_method != "POST" && m_method != "GET" && m_method != "DELETE")
            return (-2);
        if (m_method == "GET" || m_method == "POST")
        {
            if ((result = this->checkTheEndOfRequest(buffer)) == 1)
                return (-2);
        }
    }
    else if (result == -1)
        return (0);
    else if (result == 0)
    {
        std::cout << "disconnected" << std::endl;
        close(socket);
        clientSocket.erase(clientSocket.begin() + i);
        FD_CLR(socket, &(*readySockets));
        FD_CLR(socket, &(*writeSockets)); // if (m_method == "GET" || m_method == "POST" || m_method == "DELETE")
        m_requestMap.erase(socket);
        return (0);
    }
    // else
    return (result);
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

std::string Request::getContentLength(void) const
{
    std::string length;
    std::stringstream stringStream(m_contentLength);
    std::getline(stringStream, length, ' ');
    std::getline(stringStream, length, ' ');
    return (length);
}

std::string Request::getHostSolo(void) const
{
    return (this->m_hostSolo);
}

std::string Request::getPortSolo(void) const
{
    return (this->m_portSolo);
}

std::string Request::getFastCgi(void) const
{
    return (this->m_fastCgi);
}
void Request::setRequest(std::string request)
{
    this->m_request = request;
}

void Request::setBody(std::string body)
{
    this->m_body = body;
}

void Request::setFastCgi(std::string setFastCgi)
{
    this->m_fastCgi = setFastCgi;
}

Request::~Request()
{
}

std::ostream &operator<<(std::ostream &out, Request &src)
{
    // out << src.getRequest() << std::endl;
    out << src.getMethod() << std::endl;
    out << src.getPath() << std::endl;
    out << src.getVersion() << std::endl;
    out << src.getFirstRequestHeader() << std::endl;
    out << src.getHost() << std::endl;
    out << src.getUserAgent() << std::endl;
    out << src.getAccept() << std::endl;
    // out << src.getAcceptEncoding() << std::endl;
    // out << src.getAcceptLanguage() << std::endl;
    // out << src.getConnection() << std::endl;
    out << src.getBody() << std::endl;
    out << src.getRequest() << std::endl;
    out << src.getBoundary() << std::endl;
    out << src.getFileName() << std::endl;
    out << src.getBetweenBoundary() << std::endl;
    return (out);
}
// // if ((result = get_next_line(socket, &buffer)) == 0)
// {
//     std::cout << "disconnected" << std::endl;
//     close(socket);
//     clientSocket.erase(clientSocket.begin() + i);
//     FD_CLR(socket, &(*readySockets));
//     FD_CLR(socket, &(*writeSockets));
//     // init();
//     return (0);
// }
// else if (result == -1)
// {
//     return (2);
// }
// else
// {
//     std::cout << buffer << std::endl;
//     this->m_mainRequest += buffer;
//     this->m_mainRequest += "\n";
//     if (m_firstRequestheader == "")
//     {
//         this->parsingRequestLine(buffer);
//     }
//     if (m_method != "POST" && m_method != "GET" && m_method != "DELETE")
//     {
//         return (-1);
//     }
//     delete[] buffer;
//     if (m_method == "GET" || m_method == "DELETE")
//         parsingRequestGet(socket, &buffer);
//     else if (m_method == "POST")
//         parsingRequestPost(socket, &buffer);
//     return (1);
// }

// while (get_next_line(socket, &(*buffer)) > 0)
// {
// line = *buffer;
// std::cout << *buffer << std::endl;
// this->m_mainRequest += *buffer;
// this->m_mainRequest += "\n";
// if (check == 0 && ((i = line.find("boundary")) != std::string::npos))
// {
//     boundry = &line[i];
//     m_boundary = justBoundary(boundry);
//     check++;
// }
// else if (check == 2 || line.find(m_boundary) != std::string::npos)
// {
//     if (check == 2 && li----------------------------495361025204011784128785ne.find(m_boundary) != std::string::npos)
//     {
//         m_betweenBoundary += line;
//         check = 3;
//         // break;
//     }
//     m_betweenBoundary += line + '\n';
//     check = 2;
// }
// delete[](*buffer);
// }
// while ()
// this->requestHeaders(socket);
// parsingBetweenBoundary();
// this->concatenation();