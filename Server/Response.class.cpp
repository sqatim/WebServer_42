#include "Response.class.hpp"

Response::Response(/* args */) : m_type(0)
{
}

void Response::initResponse()
{
    this->m_version = "HTTP/1.1";
    this->m_contentType = "Content-Type: ";
    this->m_contentLength = "Content-Length: ";
    this->m_location = "Location: ";
    this->m_connection = "Connection: close";
}

static std::string readingTheFile(const char *filename)
{

    std::ifstream myReadFile(filename);
    std::string text;
    std::string line;

    text = "";
    while (std::getline(myReadFile, line))
    {
        text += line;
        if (!myReadFile.eof())
            text += "\n";
    }
    myReadFile.close();
    return (text);
}

void Response::contentHeader(std::string status, std::string type1, std::string type2, std::string body)
{
    m_type = ROOT;
    statusIndication(status);
    this->setContentType(type1, type2);
    this->m_body = body;
    this->m_contentLength += std::to_string(body.length());
}

void Response::defaultBody()
{
    this->m_status = "304 Not Modified";
    this->m_body = "<head>";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">";
    this->m_body += "<title>Welcome to Barnatouti!</title>";
    this->m_body += "<style>";
    this->m_body += "html { color-scheme: light dark; }";
    this->m_body += "body { width: 35em; margin: 0 auto;";
    this->m_body += "font-family: Tahoma, Verdana, Arial, sans-serif; }";
    this->m_body += "</style>";
    this->m_body += "<h1>Welcome to Barnatouti!</h1>\n";
    this->m_body += "<p>If you see this page, the Barnatouti web server is successfully \
        installed and working. Further configuration is required.</p>\n";
    this->m_body += "<p><em>Thank you for using Barnatouti.</em></p>\n";
}

void Response::notFoundBody(Parse parse, std::string root)
{
    this->m_status = "404 Not Found";
    std::string path;
    int check = 0;
    for (int i = 0; i < parse.geterror_page().size(); i++)
    {
        if (parse.geterror_page()[i].redirec == "404")
        {
            path = root;
            path.insert(path.length(), parse.geterror_page()[i].path.c_str());
            if (fileOrDir(path.c_str()) == 1)
            {
                std::cout << "shalam camarade" << std::endl;
                this->m_body = readingTheFile(path.c_str());
                check = 1;
            }
        }
    }
    if (check == 0)
    {
        this->m_body = "<html>\n";
        this->m_body += "<head>\n";
        this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
        this->m_body += "<title>404 Not Found</title>\n</head>";
        this->m_body += "<center><h1>404 Not Found</h1></center>\n";
        this->m_body += "<hr><center>Barnatouti</center>\n";
        this->m_body += "</html>";
    }
}

void Response::forbiddenBody(Parse parse, std::string root)
{
    this->m_status = "403 Forbidden";
    std::string path;
    int check = 0;
    for (int i = 0; i < parse.geterror_page().size(); i++)
    {
        if (parse.geterror_page()[i].redirec == "404")
        {
            path = root;
            path.insert(path.length(), parse.geterror_page()[i].path.c_str());
            if (fileOrDir(path.c_str()) == 1)
            {
                std::cout << "shalam camarade" << std::endl;
                this->m_body = readingTheFile(path.c_str());
                check = 1;
            }
        }
    }
    this->m_body = "<html>\n";
    this->m_body += "<head>\n";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    this->m_body += "<title>403 Forbidden</title>\n";
    this->m_body += "</head>\n";
    this->m_body += "<center><h1>403 Forbidden</h1></center>\n";
    this->m_body += "<hr><center>Barnatouti</center>\n";
    this->m_body += "</html>";
}

void Response::fileDeleted()
{
    this->m_status = "200 OK";
    this->m_body = "<html>\n";
    this->m_body += "<head>\n";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    this->m_body += "<title>Deleted</title>\n";
    this->m_body += "</head>\n";
    this->m_body += "<center><h1>File Deleted</h1></center>\n";
    this->m_body += "</html>";
}

void Response::fileUploaded()
{
    this->m_status = "200 OK";
    this->m_body = "<html>\n";
    this->m_body += "<head>\n";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    this->m_body += "<title>Uploaded</title>\n";
    this->m_body += "</head>\n";
    this->m_body += "<center><h1>File Uploaded</h1></center>\n";
    this->m_body += "</html>";
}

void Response::redirectHeader(int socket, std::string status, std::string location)
{
    m_type = REDIRECT;
    statusIndication(status);
    m_location += location;
    this->setContentType("text", "html");
    // sendRespone(socket);
}

std::string justHost(std::string host)
{
    std::stringstream stringStream(host);
    std::string result;
    std::getline(stringStream, result, ' ');
    std::getline(stringStream, result, ' ');
    // std::cout << result << std::endl;
    return (result);
}

void Response::redirectHeaderToPath(int socket, std::string status, std::string host, std::string url)
{
    std::string path;

    path = "http://";
    path += justHost(host);
    path.insert(path.length(), "/");
    path.insert(path.length(), url);
    path.insert(path.length(), "/");
    m_type = REDIRECT;
    statusIndication(status);
    m_location += path;
    std::cout << "m_location _" << m_location << std::endl;
    this->setContentType("text", "html");
    setHeader();
    setResponse();
    // sendRespone(socket);
}

std::vector<std::string> listing(const char *fileName)
{
    std::vector<std::string> list;
    struct dirent *ptr;
    DIR *dr;
    dr = opendir(fileName);
    if (dr != NULL)
    {
        for (ptr = readdir(dr); ptr != NULL; ptr = readdir(dr))
        {
            if (ptr->d_name[0] != '.' && ptr->d_name[1] != '\0')
                list.push_back(ptr->d_name);
        }
        closedir(dr);
    }
    else
        std::cout << "\nError Occurred!" << std::endl;
    return (list);
}

std::string Response::autoIndexBody(const char *fileName, const char *url)
{
    std::vector<std::string> list;
    std::string body;
    list = listing(fileName);
    body = "<html>\n";
    body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    body += "<head><title>Index of ";
    body += url;
    body += "</title></head>\n<body>\n";
    body += "<h1>Index of ";
    body += url;
    body += "</h1>\n";
    body += "<hr><pre>\n";
    for (int i = 0; i < list.size(); i++)
    {
        body += "<a href=\"" + list[i] + "\">";
        body += list[i];
        body += "</a>\n";
    }
    body += "</pre><hr></body>\n</html>";
    return (body);
}

void Response::simpleLocation()
{
}

void Response::sendResponse(int socket)
{
    setHeader();
    setResponse();
    // std::cout << m_response << std::endl;
    write(socket, m_response.c_str(), m_response.length());
}

void Response::statusIndication(std::string status)
{
    if (status == "200")
        this->m_status = "200 OK";
    else if (status == "301")
        this->m_status = "301 Moved Permanently";
    else if (status == "304")
        this->m_status = "304 Not Modified";
    else if (status == "403")
        this->m_status = "403 Forbidden";
    else if (status == "404")
        this->m_status = "404 Not Found";
    else if (status == "500")
        this->m_status = "500 Internal Server Error";
}

// ======================================Setters======================================
void Response::setVersion(std::string version)
{
    this->m_version = version;
    return;
}

void Response::setContentType(std::string type1, std::string type2)
{
    this->m_contentType += type1 + "/" + type2;
}

void Response::setLocation(std::string location)
{
    this->m_location += location;
}
void Response::setContentLength(std::string length)
{
    this->m_contentLength += length;
}

void Response::setStatus(std::string status)
{
    this->m_status = status;
    return;
}

void Response::setBody(std::string body)
{
    this->m_body = body;
    return;
}
void Response::setHeader(std::string header)
{
    this->m_header = header;
}

void Response::setResponse(std::string response)
{
    this->m_response = response;
}
void Response::setHeader()
{
    this->m_header = this->m_version;
    this->m_header += " " + this->m_status + "\n";
    this->m_header += this->m_contentType + "\n";
    if (m_type != REDIRECT)
    {
        this->m_header += this->m_contentLength + "\n";
        this->m_header += this->m_connection;
    }
    if (m_type == REDIRECT)
        this->m_header += this->m_location + "\n";
}

void Response::setResponse()
{

    this->m_response = this->m_header;
    this->m_response += "\n\n";
    if (m_type != REDIRECT)
        this->m_response += this->m_body;
}

void Response::setType(int type)
{
    this->m_type = type;
}
// ======================================Getters======================================

std::string Response::getLocation() const
{
    return m_location;
}

std::string Response::getStatus() const
{
    return this->m_status;
}

std::string Response::getHeader() const
{
    return this->m_header;
}

std::string Response::getBody() const
{
    return this->m_body;
}

std::string Response::getResponse() const
{
    return this->m_response;
}

int Response::getType() const
{
    return (this->m_type);
}

Response::~Response()
{
}
