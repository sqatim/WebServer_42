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

// param location a zadto 3lama y9ad liya amine blan
int Server::locationContinued(int i, std::string &path, std::string location)
{
    std::string root;
    int check;
    struct stat fileStat;
    this->m_response.setType(0);
    if (this->m_parse.getlocation()[i].getroot() != "")
    {
        root = this->m_parse.getlocation()[i].getroot();
        slash(&root);
    }
    // std::cout << "#################" << root << std::endl;
    if (location != "/")
    {
        root.insert(root.length(), location.c_str());
        // std::cout << "jijijaja " << root << std::endl;
    }
    if (root[ft_strlen(root.c_str()) - 1] == '/')
        root.erase(root.length() - 1);
    if (stat(root.c_str(), &fileStat) == 0)
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

void Server::location(std::string &path)
{
    int check = 0;
    int cgi;
    std::string location;
    char **array;
    std::string root;
    int cgiFound = 0;
    // khasni n9alab hta f location 3la php o py wash kaynin
    if (this->m_parse.getlocation().size() != 0)
    {
        // if ((cgi = ft_cgi(m_request.getPath().c_str()) == 1) || (cgi = ft_cgi(m_request.getPath().c_str()) == 2))
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
        //     {
        //         for (; this->m_parse.getlocation()[k].getname() != "*.py" && k < this->m_parse.getlocation().size(); k++)
        //             ;
        //     }
        //     if (this->m_parse.getlocation()[k].getname() == "*.php" || this->m_parse.getlocation()[k].getname() == "*.py")
        //     {
        //         location = root;
        //         if (location[0] == '/')
        //             location.erase(0, 1);
        //         check = locationContinued(k, path, location);
        //         cgiFound = 1;
        //     }
        //     else
        //         cgiFound = 0;
        //     // check = 0;
        // }
        if (cgiFound == 0)
        {
            for (int i = 0; i < this->m_parse.getlocation().size(); i++)
            {
                location = this->m_parse.getlocation()[i].getname();
                // slash(&location);
                location = location.c_str();
                if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
                {
                    std::cout << "************" << location << "************" << std::endl;
                    array = ft_split(m_request.getPath().c_str(), '/');
                    location = ft_joinSlash(array);
                    for (int i = 0; array[i]; i++)
                        delete array[i];
                    delete[] array;
                    if (this->m_response.checkLocation(this->m_parse.getlocation()[i]) == 1)
                    {
                        this->m_response.redirectHeader(this->m_parse.getlocation()[i].get_return()[0].redirec,
                                                        this->m_parse.getlocation()[i].get_return()[0].path);
                        check = 1;
                    }
                    else
                    {
                        if ((check = locationContinued(i, path, location)) == 1)
                            break;
                    }
                }
            }
        }
        if (check != 1)
            throw NotFound();
    }
}
void Server::manageRequest(int socket)
{
    m_response.initResponse();
    try
    {
        std::string path = "";
        int len;
        char *result;
        path = this->m_parse.getroot();
        if (path == "")
            path = "./Config";
        slash(&path);
        checkForTheIndex(this->m_parse.get_Index(), path, path);
        location(path);
        if (this->m_response.getType() == 0 || this->m_response.getType() == 2)
        {
            if (this->m_response.getType() == 0)
            {
                result = ft_strjoin(path.c_str(), this->m_parse.getIndexToUse().c_str());
                m_response.contentHeader("200", "text", "html", readingTheFile(result));
            }
            else
            {
                result = strdup(path.c_str());
                m_response.contentHeader("200", "text", "html", readingTheFile(result));
            }
        }
    }
    catch (Server::Forbidden &e)
    {
        m_response.forbiddenBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
    }
    catch (Server::NotFound &e)
    {
        m_response.notFoundBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
    }
    m_response.setHeader();
    // debug(this->m_response.getHeader());
    // this->m_response.getStatus();
    m_response.setResponse();
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}