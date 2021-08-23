#include <arpa/inet.h>
#include "Server.class.hpp"


int main()
{
    try
    {
        Parse parse("webserv.conf");
        Server server(parse);

        server.manipulation();
    }
    catch(std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}