#include "Server.class.hpp"

std::string ft_joinSlash(char **array, const char *path)
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

int fileOrDir(const char *path)
{
    struct stat fileStat;

    if (stat(path, &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IFDIR)
        {
            // std::cout << "it's a directory" << std::endl;
            return (2);
        }
        else if (fileStat.st_mode & S_IFREG)
        {
            // std::cout << "It's a file" << std::endl;
            return (1);
        }
        else
            return (3);
    }
    else
        return (0);
}

void slash(std::string *path)
{
    int len;
    if (*path != "")
    {
        len = ft_strlen(path->c_str());
        if ((*path)[len - 1] != '/')
            path->insert(len, "/");
    }
}

std::string getRoot(LocaTion &location, Parse &parse, int which)
{
    std::string root;

    if (which == 0)
    {
        if ((root = parse.getroot()) == "")
            root = "./Config";
    }
    else if (which == 1)
    {
        if ((root = location.getroot()) == "")
            if ((root = parse.getroot()) == "")
                root = "./Config";
    }
    return (root);
}

int getIndex(LocaTion &location, Parse &parse, int which, std::string &root)
{
    std::vector<std::string> index;
    std::string path;

    index.push_back("index.html");
    if (which == 0)
    {
        if (parse.get_Index().size() != 0)
            index = parse.get_Index();
    }
    else if (which == 1)
    {
        if (location.getindex().size() != 0)
        {
            index = location.getindex();
        }
        else if (parse.get_Index().size() != 0)
            index = parse.get_Index();
    }
    for (size_t i = 0; i < index.size(); i++)
    {
        path = root;
        slash(&path);
        path.insert(path.length(), index[i].c_str());
        if (fileOrDir(path.c_str()) == 1)
        {
            root = path;
            return (1);
        }
    }
    return (0);
}

size_t ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}