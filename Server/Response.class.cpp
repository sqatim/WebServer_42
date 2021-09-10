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

void Response::contentHeader(std::string status, std::string type1, std::string type2, std::string body)
{
    statusIndication(status);
    this->setContentType(type1, type2);
    std::cout << body << std::endl;
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

void Response::notFoundBody()
{
    this->m_status = "404 Not Found";
    this->m_body = "<html>\n";
    this->m_body += "<head>\n";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    this->m_body += "<title>404 Not Found</title>\n</head>";
    this->m_body += "<center><h1>404 Not Found</h1></center>\n";
    this->m_body += "<hr><center>Barnatouti</center>\n";
    this->m_body += "</html>";
}

void Response::forbiddenBody()
{
    this->m_status = "403 Forbidden";
    this->m_body = "<html>\n";
    this->m_body += "<head>\n";
    this->m_body += "<link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta charset=\"UTF-8\">\n";
    this->m_body += "<title>403 Forbidden</title>\n";
    this->m_body += "</head>\n";
    this->m_body += "<center><h1>403 Forbidden</h1></center>\n";
    this->m_body += "<hr><center>Barnatouti</center>\n";
    this->m_body += "</html>";
}

int Response::checkLocation(LocaTion location)
{
    if (location.get_return().size() != 0)
        return (1);
    return (0);
}
void Response::redirectHeader(std::string status, std::string location)
{
    m_type = REDIRECT;
    statusIndication(status);
    m_location += location;
    this->setContentType("text", "html");
}

void Response::simpleLocation()
{
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
