#include "Server.class.hpp"

static std::string ft_joinSlash(char **array, const char *path)
{
    std::string str = "";
    int len;
    for (int i = 0; array[i]; i++)
    {
        len = ft_strlen(str.c_str());
        str.insert(len, array[i]);
        len = ft_strlen(str.c_str());
        if (array[i + 1] || path[ft_strlen(path) - 1] == '/')
            str.insert(len, "/");
    }
    return (str.c_str());
}

static void slash(std::string *path)
{
    int len;
    if (*path != "")
    {
        len = ft_strlen(path->c_str());
        if ((*path)[len - 1] != '/')
            path->insert(len, "/");
    }
}

static int ft_comparaison(std::string location, std::string uri)
{
    int i;

    for (i = 0; location.c_str()[i]; i++)
    {
        if (i == 0 && (location.c_str()[0] == '/' && uri.c_str()[0] == '/'))
            i++;
        if (location.c_str()[i] == '/' && location.c_str()[i + 1] == '\0')
            break;
        if (location[i] != uri[i] || (location.c_str()[i] == '/' && location.c_str()[i + 1] == '/'))
            return (0);
    }
    return (1);
}

static int ft_cgi(std::string path)
{
    int len;

    len = ft_strlen(path.c_str());
    if (len >= 4 && path[len - 1] == 'p' && path[len - 2] == 'h' && path[len - 3] == 'p' && path[len - 4] == '.')
    {
        return (1);
    }
    if (len >= 3 && path[len - 1] == 'p' && path[len - 2] == 'y' && path[len - 3] == '.')
        return (2);

    return (0);
}

std::string getroot(LocaTion &location, Parse &parse, int which)
{
    std::string root;

    if (which == 0)
    {
        if ((root = parse.getroot()) == "")
            root = "./Config";
    }
    if (which == 1)
    {
        if ((root = location.getroot()) == "")
            if ((root = parse.getroot()) == "")
                root = "./Config";
    }
    // slash(&root);
    return (root);
}

int appendLocation(int i, std::string &path, LocaTion location)
{
    // std::string root;
    int check;
    struct stat fileStat;
    // std::cout << "#################" << root << std::endl;
    if (location.getname() != "/")
        path.insert(path.length(), location.getname().c_str());
    // if (root[ft_strlen(root.c_str()) - 1] == '/')
    // root.erase(root.length() - 1);
    if (stat(path.c_str(), &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IFREG)
        {
            path = root.c_str();
            this->m_response.setType(2);
            std::cout << "It's a file" << std::endl;
            return (1);
        }
    }
    else
        return (0);
    slash(&root);
    // debug(root);
    if (this->m_parse.getlocation()[i].getindex().size() != 0)
        check = checkForTheIndex(this->m_parse.getlocation()[i].getindex(), root, path);
    else
        check = checkForTheIndex(this->m_parse.get_Index(), root, path);
    return (check);
}

int fastCgi(Request &request, Parse &parse)
{
    int cgi;
    std::string root;
    int check;
    if ((cgi = ft_cgi(request.getPath().c_str()) == 1) || (cgi = ft_cgi(request.getPath().c_str()) == 2))
    {
        int k = 0;
        if (cgi == 1)
            while (parse.getlocation()[k].getname() != "*.php" && k < parse.getlocation().size())
                k++;
        else
            while (parse.getlocation()[k].getname() != "*.py" && k < parse.getlocation().size())
                k++;
        if (parse.getlocation()[k].getname() == "*.php" || parse.getlocation()[k].getname() == "*.py")
        {

            root = getroot(parse.getlocation()[k], parse, 1);
            check = appendLocation(k, root, parse.getlocation()[k]);
            cgiFound = 1;
        }
        else
        // check = 0;
    }
}

void wich(std::string location)
{
    //if ((cgi = ft_cgi(m_request.getPath().c_str()) == 1) || (cgi = ft_cgi(m_request.getPath().c_str()) == 2))
    // {
    //     root = m_request.getPath().c_str();
    //     int k = 0;
    //     std::cout << "-------------" << root << "-------------" << std::endl;
    //     if (cgi == 1)
    //     {
    //         for (; this->m_parse.getlocation()[k].getname() != "*.php" && k < this->m_parse.getlocation().size(); k++)
    //             ;
    //     }
    //     else
    //         for (; this->m_parse.getlocation()[k].getname() != "*.py" && k < this->m_parse.getlocation().size(); k++)
    //             ;
    //     if (this->m_parse.getlocation()[k].getname() == "*.php" || this->m_parse.getlocation()[k].getname() == "*.py")
    //     {
    //         location = root;
    //         if (location[0] == '/')
    //             location.erase(0, 1);
    //         check = locationContinued(k, path, location);
    //         cgiFound = 1;
    //     }
    //     else
    //     // check = 0;
    // }
}
void Server::location(int socket, std::string &path)
{
    int check = 0;
    int cgi;
    std::string location;
    char **array;
    std::string root;
    int cgiFound = 0;
    // khasni n9alab hta f location 3la php o py wash kaynin
    for (int i = 0; i < this->m_parse.getlocation().size(); i++)
    {
        location = this->m_parse.getlocation()[i].getname();
        location = location.c_str();
        if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
        {
            array = ft_split(m_request.getPath().c_str(), '/');
            location = ft_joinSlash(array, m_request.getPath().c_str());
            std::cout << "************" << location << "************" << std::endl;
            for (int i = 0; array[i]; i++)
                delete array[i];
            delete[] array;
            if (this->m_response.checkLocation(this->m_parse.getlocation()[i]) == 1)
            {
                this->m_response.redirectHeader(socket, this->m_parse.getlocation()[i].get_return()[0].redirec,
                                                this->m_parse.getlocation()[i].get_return()[0].path);
                check = 1;
            }
            else if ((check = locationContinued(i, path, location)) == 1)
                break;
        }
    }
    if (check != 1)
        throw NotFound();
}