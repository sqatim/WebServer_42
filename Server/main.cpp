#include <arpa/inet.h>
#include "WebServer.class.hpp"

int main()
{
    try
    {
        WebServ parse("webserv.conf");
        WebServer webServer(parse);
        for (size_t i = 0; i < parse.getwebserv().size(); i++)
        {
            webServer.setServer(parse.getwebserv()[i]);
        }
        webServer.run();
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}