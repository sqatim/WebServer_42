#include "Request.class.hpp"
#include <sstream>

int hexaToInt(std::string hexa)
{
    int result;
    std::stringstream stream;
    stream << std::hex << hexa;
    stream >> result;
    return (result);
}
std::string dataToBackSlashR(std::string str)
{
    std::string data = "";
    for (int i = 0; str[i]; i++)
    {
        data += str[i];
        if (str[i + 1] == '\r')
            break;
        if (str[i + 1] == '\n')
            break;
    }
    data += "\0";
    return data;
}

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
    m_contentType = "";
    m_transferEncoding = "";
    m_chunked.clear();
    m_bodyPost.clear();
    m_keyValue.clear();
}

Request::Request() : m_method(""), m_path(""), m_version(""), m_firstRequestheader(""), m_host(""),
                     m_hostSolo(""), m_portSolo(""), m_userAgent(""), m_accept(""), m_cookie(""),
                     m_fastCgi(""), m_contentType(""), m_transferEncoding(""), m_contentLength(""),
                     m_fileName(""), m_betweenBoundary(""), m_boundary("11111111"),
                     m_countContentLength(0), m_check(0), m_body(""), m_request(""), m_mainRequest("")
{
}

void Request::parseHost(std::string host)
{
    std::stringstream stringStream(host);
    std::getline(stringStream, m_hostSolo, ' ');
    std::getline(stringStream, m_portSolo, ' ');
}

void Request::parsingKeyValue(std::string body)
{
    std::stringstream stringStream(body);
    std::stringstream keyValue;
    std::string line;
    std::string parseKeyValue;
    int counter = 0;
    int i = 0;
    line = "";
    while (std::getline(stringStream, line, '&'))
    {
        m_keyValue.push_back({"", ""});
        keyValue.clear();
        keyValue.str(line);
        counter = 0;
        while (std::getline(keyValue, parseKeyValue, '='))
        {
            if (counter == 0)
            {
                m_keyValue[i].key = parseKeyValue;
                counter++;
            }
            else
                m_keyValue[i].value = parseKeyValue;
        }
        i++;
    }
}

int Request::requestHeaders(int socket)
{
    std::istringstream stringStream(m_requestMap[socket]);
    std::string line;
    std::string ss = "";
    std::string host;
    std::string value;
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
            host = justValue(line);
        }
        if (m_boundary == "11111111" && (i = line.find("boundary=") != std::string::npos))
        {
            i = line.find("boundary=");
            m_boundary = &line[i + 9];
        }
        if (m_userAgent == "" && line.compare(0, 12, "User-Agent: ") == 0)
            m_userAgent = line;
        if (m_accept == "" && line.compare(0, 8, "Accept: ") == 0)
            m_accept = line;
        if (m_cookie == "" && line.compare(0, 8, "Cookie: ") == 0)
            m_cookie = line;
        if (m_contentLength == "" && line.compare(0, 16, "Content-Length: ") == 0)
            m_contentLength = line;
        if (m_contentType == "" && line.compare(0, 14, "Content-Type: ") == 0)
            m_contentType = line;
    }
    if (m_method == "POST")
    {
        value = justValue(m_contentType);
        if (value == "multipart/form-data;")
            parsingBetweenBoundary();
        else if (value == "application/x-www-form-urlencoded")
            parsingKeyValue(m_body);
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
    size_t i;
    std::string keyValue;
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
    if ((i = this->m_path.find("?")) != std::string::npos)
    {
        keyValue = &this->m_path[i + 1];
        this->m_path[i] = '\0';
        this->m_path = this->m_path.c_str();
        parsingKeyValue(keyValue);
    }
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
    std::string file;
    std::stringstream stream;
    std::string line;
    for (size_t i = 0; i < m_bodyPost.size(); i++)
    {
        file = path;
        file.insert(file.length(), m_bodyPost[i].filename);
        std::ofstream myWriteFile(file);
        stream.str(m_bodyPost[i].m_body);
        std::getline(stream, line, '\r');
        line = line.c_str();
        myWriteFile << line;
        stream.clear();
        myWriteFile.close();
    }
}

void Request::parsingBetweenBoundary()
{
    std::stringstream countBoundary(m_body);
    std::string buffer = m_body;
    std::stringstream stringStream(buffer);
    std::string line;
    size_t filename;
    int counter = 0;
    int i = 0;
    int l = 0;
    int check = 0;
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
            m_bodyPost[0].filename += "\0";
            l = 0;
            while (std::getline(stringStream, line, '\r') && l < 2)
            {
                l++;
            }
            if (m_transferEncoding == "chunked")
                line = &line[2];
            else
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
            m_bodyPost[i].filename += "\0";
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            std::getline(stringStream, line, '\r');
            if (m_transferEncoding == "chunked")
                line = &line[2];
            else
                line = &line[1];
            if (line.c_str()[line.length() - 1] == '\n')
                line[line.length() - 1] = '\0';
            m_bodyPost[i].m_body = line;
        }
        i++;
    }
}

int Request::parsingRequestPost(char *buffer)
{
    std::stringstream stringStream(buffer);
    std::stringstream string;
    std::string removeBackSlashR;
    std::string line(buffer);
    std::string boundry;
    std::string body;
    size_t i = 0;
    size_t j = 0;

    if (m_check == 0)
    {
        if ((i = line.find("Content-Length: ")) != std::string::npos && m_contentLength == "")
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
        while ((int)m_countContentLength < std::atoi(m_contentLength.c_str()) && m_countContentLength < body.length())
        {
            m_body += body[i];
            i++;
            m_countContentLength++;
        }
        if ((int)m_countContentLength == std::atoi(m_contentLength.c_str()))
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

int Request::checkTheEndOfRequestGetAndDelete(char *buffer)
{
    std::stringstream stringStream(buffer);
    std::string line;
    std::string request = "";
    std::stringstream stream;

    if (m_method == "GET" || m_method == "DELETE")
    {
        while (std::getline(stringStream, line, '\r'))
            request += line;
        line = "";
        stream.str(request);
        while (std::getline(stream, line, '\n'))
        {
            if (line[0] == '\r' || line[0] == '\0')
                return (1);
        }
    }
    return (0);
}
int Request::checkTheEndOfRequest(char *buffer)
{

    std::string test;
    std::string chuncked;
    std::stringstream stringStream(buffer);
    std::stringstream stream;
    std::string line;
    std::string request = "";
    int length;
    size_t i = 0;
    std::string body;
    int counter = 0;
    if (checkTheEndOfRequestGetAndDelete(buffer))
        return (1);
    else if (m_method == "POST")
    {
        line = buffer;
        if (m_check == 0)
        {
            if ((i = line.find("Transfer-Encoding: chunked")) != std::string::npos || m_transferEncoding == "chunked")
            {
                m_transferEncoding = "chunked";
                if (line.find("application/x-www-form-urlencoded") != std::string::npos || m_contentType == "application/x-www-form-urlencoded")
                {
                    m_contentType = "application/x-www-form-urlencoded";
                    m_chunked.push_back({0, 0, 0, ""});
                    i = line.find("\r\n\r\n");
                    i += 4;
                    line = &line[i];
                    length = hexaToInt(dataToBackSlashR(line));
                    m_chunked[counter].length = length;
                    i = line.find("\r\n");
                    i += 2;
                    line = &line[i];
                    m_chunked[counter].m_body = dataToBackSlashR(line);
                    m_chunked.push_back({0, 0, 0, ""});
                }
                else if (line.find("multipart/form-data;") != std::string::npos || m_contentType == "multipart/form-data;")
                {
                    m_contentType = "multipart/form-data;";
                    if (m_chunked.size() == 0)
                    {
                        m_chunked.push_back({0, 0, 0, ""});
                        i = line.find("\r\n\r\n");
                        i += 4;
                        line = &line[i];
                        length = hexaToInt(dataToBackSlashR(line));
                        m_chunked[m_chunked.size() - 1].length = length;
                        length = ft_strlen(dataToBackSlashR(line).c_str()) + 2;
                        line = &line[length];
                        size_t p;
                        for (p = 0; p < m_chunked[m_chunked.size() - 1].length; p++)
                        {
                            m_chunked[m_chunked.size() - 1].m_body += line[p];
                        }
                        m_chunked[m_chunked.size() - 1].m_body += '\0';
                    }
                    else
                    {
                        for (int j = 0; line[j]; j++)
                        {
                            // std::cout << "i am here" << std::endl;
                            m_chunked.push_back({0, 0, 0, ""});
                            length = hexaToInt(dataToBackSlashR(&line[j]));
                            m_chunked[m_chunked.size() - 1].length = length;
                            length = ft_strlen(dataToBackSlashR(&line[j]).c_str()) + 2;
                            j += length;
                            size_t p;
                            for (p = 0; p < m_chunked[m_chunked.size() - 1].length; p++)
                            {
                                m_chunked[m_chunked.size() - 1].m_body += line[j];
                                j++;
                            }
                            if (m_chunked[m_chunked.size() - 1].length != 0)
                                m_chunked[m_chunked.size() - 1].m_body += '\0';
                        }
                    }
                }
                m_check = 2;
            }
            else if ((i = line.find("Content-Length: ")) != std::string::npos)
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
            i = 0;
            while ((int)m_countContentLength < std::atoi(m_contentLength.c_str()) && i < body.length())
            {
                m_body += body[i];
                i++;
                m_countContentLength++;
            }
            if ((int)m_countContentLength == std::atoi(m_contentLength.c_str()))
                return (1);
        }
        if (m_check == 2)
        {
            if (m_chunked.size() != 0 && m_chunked[m_chunked.size() - 1].length == 0)
            {
                for (size_t l = 0; l < m_chunked.size(); l++)
                {
                    m_body += m_chunked[l].m_body;
                }
                return (1);
            }
            m_check = 0;
        }
    }
    return (0);
}

int Request::readingRequest(int socket, int &result)
{
    char buffer[2500];

    if ((result = read(socket, buffer, 2500)) > 0)
    {
        buffer[result] = '\0';
        m_requestMap[socket] += buffer;
        if (m_firstRequestheader == "")
            this->parsingRequestLine(buffer);
        if (m_method != "POST" && m_method != "GET" && m_method != "DELETE")
            return (1);
        if (m_method == "GET" || m_method == "POST" || m_method == "DELETE")
        {
            if ((result = this->checkTheEndOfRequest(buffer)) == 1)
                return (1);
        }
    }
    return (0);
}
int Request::concatRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i)
{
    int result;

    if (readingRequest(socket, result) == 1)
        return (-2);
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