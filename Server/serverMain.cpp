#include <arpa/inet.h>
#include "Server.class.hpp"

int main()
{
    try
    {
        WebServ parse("webserv.conf");
        // for (int i = 0; i < parse.getwebserv().size(); i++)
        // {
        //     Server server(parse.getwebserv()[i]);
        //     server.manipulation();
        // }
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}