#include <arpa/inet.h>
#include "Server.class.hpp"


int main()
{
    try
    {
        Server server;
        server.manipulation();
    }
    catch(std::string error)
    {
        std::cout << error << std::endl;
    }
    return (0);
}