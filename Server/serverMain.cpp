#include <arpa/inet.h>
#include "Server.class.hpp"

int main()
{
    try
    {
        Parse parse("webserv.conf");
        std::cout << parse ;
        // Server server(parse);
        // server.manipulation(parse);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}