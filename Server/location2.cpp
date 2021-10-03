#include "Server.class.hpp"

// la contunie du location 1 et des fonction utiles

int ft_comparaison(std::string location, std::string url)
{
    int i;

    for (i = 0; location.c_str()[i]; i++)
    {
        if (location == "/")
            return 1;
        if (i == 0 && (location.c_str()[0] == '/' && url.c_str()[0] == '/'))
            i++;
        if (location.c_str()[i] == '/' && location.c_str()[i + 1] == '\0')
            break;
        if (location[i] != url[i] || (location.c_str()[i] == '/' && location.c_str()[i + 1] == '/'))
            return (0);
    }
    return (1);
}

int ft_cgi(std::string path)
{
    int len;

    len = ft_strlen(path.c_str());
    if (len >= 4 && path[len - 1] == 'p' && path[len - 2] == 'h' && path[len - 3] == 'p' && path[len - 4] == '.')
        return (1);
    if (len >= 3 && path[len - 1] == 'y' && path[len - 2] == 'p' && path[len - 3] == '.')
    {
                return (2);
    }
    return (0);
}

int checkLocation(LocaTion location)
{
    if (location.get_return().size() != 0)
        return (2);
    return (0);
}

int appendUrlCgi(std::string &path, LocaTion location, std::string url)
{
    int check;
    if (location.getname() != "/")
        path.insert(path.length(), url.c_str());
    std::cout << "path [" << path << "]" << std::endl;
    check = fileOrDir(path.c_str());
    return (check);
}

std::string getUrl(Request &request)
{
    char **array;
    std::string url;

    array = ft_split(request.getPath().c_str(), '/');
    url = ft_joinSlash(array, request.getPath().c_str());
    for (int i = 0; array[i]; i++)
        delete array[i];
    delete[] array;
    return (url);
}
