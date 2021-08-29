#include "Server.class.hpp"

std::string defaultBody(std::string &body)
{
    body = "<h1>Welcome to Barnatouti!</h1>\n";
    body += "<p>If you see this page, the Barnatouti web server is successfully \
        installed and working. Further configuration is required.</p>\n";
    body += "<p><em>Thank you for using Barnatouti.</em></p>\n";
    return ("304 Not Modified");
}

std::string Server::NotFound::notFoundBody(std::string &body) throw()
{
    body = "<center><h1>404 Not Found</h1></center>\n";
    body += "<hr><center>Barnatouti</center>\n";
    return ("404 Not Found");
}

std::string Server::Forbidden::forbiddenBody(std::string &body) throw()
{
    body = "<center><h1>403 Forbidden</h1></center>\n";
    body += "<hr><center>Barnatouti</center>\n";
    return ("403 Forbidden");
}

// hta nriglha man ba3d