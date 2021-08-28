#include "server.hpp"

t_header affectationHeader(std::string status, std::string type1, std::string type2, int length)
{
    t_header header;

    header.version = "HTTP/1.1";
    header.status = status;
    header.contentType = type1;
    header.contentType += "/";
    header.contentType += type2;
    header.contentLength = length;
    return header;
}

std::string responseConcatenation(t_header header, std::string body)
{
    std::string response;

    response = header.version;
    response += " ";
    response += header.status;
    response += "\n";
    response += "Content-Type: ";
    response += header.contentType;
    response += "\n";
    response += "Content-Length: ";
    response += header.contentLength;
    response += "\n\n";
    // response += "Location: http://www.facebook.com";
    response += body;
    return (response);
}