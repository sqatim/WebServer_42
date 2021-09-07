#include "Server.class.hpp"

int ft_strlen(std::string str)
{
    int i;

    i = 0;
    while (str.c_str()[i])
        i++;
    return (i);
}
std::string Server::readingTheFile(std::string filename)
{

    std::ifstream myReadFile(filename);
    std::string text;
    std::string line;
    debug(filename);
    // std::cout << myReadFile.is_open() << std::endl;
    // 3andi msushkulll hna fash kan9alab 3la file wash kayn ola la
    if (!myReadFile.is_open())
    {
        debug("wa saaaaaamiir");
        throw Server::Forbidden();
    }
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
        len = ft_strlen(*path);
        if ((*path)[len - 1] != '/')
            *path += "/";
    }
}

int Server::checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path)
{
    int len;
    std::ifstream indexFile;
    std::string pathForTest;
    // slash(&pathForTest);
    if (index.size() == 0)
    {
        if (this->m_parse.getIndexToUse() == "")
            this->m_parse.setIndexToUse("index.html");
        pathForTest = root + "index.html";
        // debug(pathForTest);
        indexFile.open(pathForTest);
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
            pathForTest = root + index[i];
            indexFile.open(pathForTest);
            // debug(pathForTest);
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

int Server::locationContinued(int i, std::string &path)
{
    std::string root;
    int check;

    this->m_response.setType(0);
    if (this->m_parse.getlocation()[i].getroot() != "")
    {
        root = this->m_parse.getlocation()[i].getroot();
        slash(&root);
    }
    // 3nadi mushkil hna dyal slash hta n9ado ghada
    // ##/Users/sqatim/Desktop/testNginx//wordpress##
    if (this->m_parse.getlocation()[i].getname() != "/")
    {

        if (root[root.length() - 1] == '/')
            root[root.length() - 1] = '\0';
        root += this->m_parse.getlocation()[i].getname();
    }
    slash(&root);
    if (this->m_parse.getlocation()[i].getindex().size() != 0)
        check = checkForTheIndex(this->m_parse.getlocation()[i].getindex(), root, path);
    else
        check = checkForTheIndex(this->m_parse.get_Index(), root, path);
    return (check);
}

void Server::location(std::string &path)
{
    int check;

    if (this->m_parse.getlocation().size() != 0)
    {
        for (int i = 0; i < this->m_parse.getlocation().size(); i++)
        {
            if (m_request.getPath() == this->m_parse.getlocation()[i].getname())
            {
                if (this->m_response.checkLocation(this->m_parse.getlocation()[i]) == 1)
                {
                    this->m_response.redirectHeader(this->m_parse.getlocation()[i].get_return()[0].redirec,
                                                    this->m_parse.getlocation()[i].get_return()[0].path);
                    check = 1;
                }
                else
                {
                    if ((check = locationContinued(i, path)) == 1)
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

        path = this->m_parse.getroot();
        if (path == "")
            path = "./Config";
        slash(&path);
        checkForTheIndex(this->m_parse.get_Index(), path, path);
        location(path);
        if (this->m_response.getType() == 0)
        {
            path += this->m_parse.getIndexToUse();
            // debug(path);
            m_response.contentHeader("200", "text", "html", readingTheFile(path));
            // debug(this->m_response.getHeader());
            // debug(m_response.getHeader());
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
    m_response.setResponse();
    // debug(m_response.getResponse());
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}