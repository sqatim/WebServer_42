#include "Server.class.hpp"

char *ft_strjoin(char const *s1, char const *s2)
{
    char *p;
    size_t i;
    size_t j;
    size_t k;

    i = 0;
    j = 0;
    k = 0;
    if (s1 && s2)
    {
        p = new char[sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)];
        if (p == NULL)
            return (NULL);
        while (s1[j])
        {
            p[i++] = s1[j++];
        }
        while (s2[k])
        {
            p[i++] = s2[k++];
        }
        p[i] = '\0';
        return (p);
    }
    return (NULL);
}
int ft_strlen(std::string str)
{
    int i;

    i = 0;
    while (str.c_str()[i])
        i++;
    return (i);
}
std::string Server::readingTheFile(char *filename)
{

    std::ifstream myReadFile(filename);
    std::string text;
    std::string line;

    delete[] filename;
    if (!myReadFile)
        throw Server::Forbidden();
    text = "";
    while (std::getline(myReadFile, line))
    {
        text += line;
        if (!myReadFile.eof())
            text += "\n";
    }
    myReadFile.close();
    return (text);
}

int Server::checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path)
{
    int len;
    std::ifstream indexFile;
    char *pathForTest;
    // slash(&pathForTest);
    if (index.size() == 0)
    {
        if (this->m_parse.getIndexToUse() == "")
            this->m_parse.setIndexToUse("index.html");
        slash(&root);
        pathForTest = ft_strjoin(root.c_str(), "index.html");
        indexFile.open(pathForTest);
        delete pathForTest;
        if (indexFile)
        {
            path = root;
            indexFile.close();
            return 1;
        }
        indexFile.close();
        return (0);
    }
    else
    {
        slash(&root);
        for (int i = 0; i < index.size(); i++)
        {
            pathForTest = ft_strjoin(root.c_str(), index[i].c_str());
            indexFile.open(pathForTest);
            delete pathForTest;
            if (indexFile)
            {
                this->m_parse.setIndexToUse(index[i]);
                path = root;
                indexFile.close();
                return 1;
            }
            indexFile.close();
        }
    }
    return (0);
}

int ft_comparaison(std::string location, std::string uri)
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
int ft_cgi(std::string path)
{
    int len;

    len = ft_strlen(path.c_str());
    if (path[len - 1] == '/')
        path[--len] = '\0';
    if (len >= 4 && path[len - 1] == 'p' && path[len - 2] == 'h' && path[len - 3] == 'p' && path[len - 4] == '.')
    {
        return (1);
    }
    if (len >= 3 && path[len - 1] == 'p' && path[len - 2] == 'y' && path[len - 3] == '.')
        return (2);

    return (0);
}

std::string ft_joinSlash(char **array)
{
    std::string str = "";
    int len;
    for (int i = 0; array[i]; i++)
    {
        len = ft_strlen(str.c_str());
        str.insert(len, array[i]);
        len = ft_strlen(str.c_str());
        if (array[i + 1])
            str.insert(len, "/");
    }
    return (str.c_str());
}
void Server::manageRequest(int socket)
{
    // std::cout << this->m_request.getMethod() << std::endl;
    if (this->m_request.getMethod() == "GET")
        getMethod(socket);
}