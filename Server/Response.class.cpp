#include "Response.class.hpp"

Response::Response(/* args */)
{
}

void Response::initResponse()
{
    this->m_version = "HTTP/1.1";
    this->m_contentType = "Content-Type: ";
    this->m_contentLength = "Content-Length: ";
    this->m_connection = "Connection: close";
}

void Response::contentHeader(std::string status, std::string type1, std::string type2, std::string body)
{
    this->m_status = status;
    this->setContentType(type1, type2);
    this->m_body = body;
    // std::cout << "********************************" << std::endl;
    // std::cout << this->m_body << std::endl;
    // std::cout << "********************************" << std::endl;
    this->m_contentLength += std::to_string(body.length());
}

void Response::defaultBody()
{
    this->m_status = "304 Not Modified";
    this->m_body = "<h1>Welcome to Barnatouti!</h1>\n";
    this->m_body += "<p>If you see this page, the Barnatouti web server is successfully \
        installed and working. Further configuration is required.</p>\n";
    this->m_body += "<p><em>Thank you for using Barnatouti.</em></p>\n";
}

void Response::notFoundBody()
{
    this->m_status = "404 Not Found";
    this->m_body = "<center><h1>404 Not Found</h1></center>\n";
    this->m_body += "<hr><center>Barnatouti</center>\n";
}

void Response::forbiddenBody()
{
    this->m_status = "403 Forbidden";
    this->m_body = "<center><h1>403 Forbidden</h1></center>\n";
    this->m_body += "<hr><center>Barnatouti</center>\n";
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
    this->m_header += this->m_contentLength + "\n";
    this->m_header += this->m_connection;
    // std::cout << "=================================" << std::endl;
    // std::cout << "content lenght: " << this->m_contentLength << std::endl;
    // std::cout << "=================================" << std::endl;
}

void Response::setResponse()
{
    this->m_response = this->m_header;
    this->m_response += "\n\n";
    this->m_response += this->m_body;
}
// ======================================Getters======================================
std::string Response::getStatus() const
{
    return this->m_status;
}

std::string Response::getBody() const
{
    return this->m_body;
}

std::string Response::getResponse() const
{
    return this->m_response;
}

Response::~Response()
{
}