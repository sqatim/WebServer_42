#include <arpa/inet.h>
#include "WebServer.class.hpp"

int main()
{
    try
    {
        WebServ parse("webserv.conf");
        WebServer webServer(parse);
        for (int i = 0; i < parse.getwebserv().size(); i++)
        {
            webServer.setServer(parse.getwebserv()[i]);
            // server.manipulation();
        }
        // for (int i = 0; i < webServer.getServer().size(); i++)
        // std::cout << webServer.getServer()[i] << std::endl;
        webServer.run();
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}