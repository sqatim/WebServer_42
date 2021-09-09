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
    // debug(filename);
    if (!myReadFile)
        throw Server::Forbidden();
    text = "\0";
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
        // std::cout << "trying: " << root.c_str() << std::endl;
        pathForTest = ft_strjoin(root.c_str(), "index.html");
        indexFile.open(pathForTest);
        // debug(pathForTest);
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
    if (location != "/")
    {
        if (root[root.length() - 1] == '/')
            root[root.length() - 1] = '\0';
        root.insert(root.length() - 1, location.c_str());
    }
    if (stat(root.c_str(), &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IFDIR)
        {
            std::cout << "It's a directory" << std::endl;
        }
        else if (fileStat.st_mode & S_IFREG)
        {
            std::cout << "It's a file" << std::endl;
        }
    }
    std::cout << root.c_str() << std::endl;
    slash(&root);

    if (this->m_parse.getlocation()[i].getindex().size() != 0)
        check = checkForTheIndex(this->m_parse.getlocation()[i].getindex(), root, path);
    else
        check = checkForTheIndex(this->m_parse.get_Index(), root, path);
    return (check);
}

void Server::location(std::string &path)
{
    int check = 0;
    const char *str;
    std::string location;
    if (this->m_parse.getlocation().size() != 0)
    {
        for (int i = 0; i < this->m_parse.getlocation().size(); i++)
        {
            // hadi zadtha gha 3la 9bal slash lakhra dyal location
            location = this->m_parse.getlocation()[i].getname();
            str = this->m_parse.getlocation()[i].getname().c_str();
            for (int j = location.length() - 1; (str[j] == '/' && j != 0); j--)
                location[j] = '\0';
            location = location.c_str();
            // this->m_parse.getlocation()[i].setname(location.c_str());
            // std::cout << "location name: " << this->m_parse.getlocation()[i].getname() << std::endl;
            // *********************************
            if (m_request.getPath() == location)
            {
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
        if (this->m_response.getType() == 0)
        {
            result = ft_strjoin(path.c_str(), this->m_parse.getIndexToUse().c_str());
            // debug(result);
            m_response.contentHeader("200", "text", "html", readingTheFile(result));
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