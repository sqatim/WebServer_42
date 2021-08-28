#include "Server.class.hpp"

std::string defaultBody()
{
    std::string defaultBody;
    defaultBody = "<h1>Welcome to Barnatouti!</h1>\n";
    defaultBody += "<p>If you see this page, the Barnatouti web server is successfully \
        installed and working. Further configuration is required.</p>\n";
    defaultBody += "<p><em>Thank you for using Barnatouti.</em></p>\n";
    return (defaultBody);
}

std::string notFountBody()
{
    std::string notFountBody;
    notFountBody = "<center><h1>404 Not Found</h1></center>\n";
    notFountBody += "<hr><center>nginx/1.21.1</center>\n";
    return (notFountBody);
}