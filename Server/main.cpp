#include <arpa/inet.h>
#include "WebServer.class.hpp"

int main(int ac, char **av)
{
    try
    {
        std::string file;
        if (ac > 2)
            throw std::string("you need to enter one Config File");
        else if (ac == 1)
        {
            file = "./Config/ConfigurationFiles/default.conf";
            if (fileOrDir(file.c_str()) == 0)
                throw std::string("Default ConfigFile not found");
        }
        else
        {
            if (fileOrDir(av[1]) == 0)
                throw std::string("Configuration file not found");
            file = av[1];
        }
        WebServ parse(file);
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