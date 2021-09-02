#include <arpa/inet.h>
#include "Server.class.hpp"
// #include ""
#include "../Parsing/webserv.hpp"

int main()
{
    try
    {
        WebServ *webserv = new WebServ("webserv.conf");
        // Parse parse("webserv.conf");
        // std::cout << parse ;
        // Server server(parse);
        // server.manipulation(parse);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}