#include "Server.class.hpp"

int ft_strlen(std::string str)
{
    int i;

    i = 0;
    while (str.c_str()[i])
        i++;
    return (i);
}
std::string readingTheFile(std::string filename)
{

    std::ifstream myReadFile;
    std::string text;
    std::string line;
    myReadFile.open(filename);
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
        len = ft_strlen(*path);
        if ((*path)[len - 1] != '/')
            *path += "/";
    }
}

int Server::checkForTheIndex(std::vector<std::string> index, std::string root)
{
    int len;
    std::ifstream indexFile;
    std::string path;
    slash(&path);
    if (index.size() == 0)
    {
        this->m_parse.setIndexToUse("index.html");
        path = root + "index.html";
        indexFile.open(path);
        if (indexFile)
        {
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
            path = root + index[i];
            indexFile.open(path);
            debug(path);
            if (indexFile)
            {
                this->m_parse.setIndexToUse(index[i]);
                indexFile.close();
                return 1;
            }
            indexFile.close();
        }
    }
    return (0);
}

int Server::locationContinued(int i)
{
    std::string path;
    int check;

    this->m_response.setType(0);
    if (this->m_parse.getlocation()[i].getroot() != "")
    {
        path = this->m_parse.getlocation()[i].getroot();
        slash(&path);
    }
    // 3nadi mushkil hna dyal slash hta n9ado ghada
    // ##/Users/sqatim/Desktop/testNginx//wordpress##
    if (this->m_parse.getlocation()[i].getname() != "/")
        path += this->m_parse.getlocation()[i].getname();
    // debug(path);
    slash(&path);
    if (this->m_parse.getlocation()[i].getindex().size() != 0)
        check = checkForTheIndex(this->m_parse.getlocation()[i].getindex(), path);
    else
        check = checkForTheIndex(this->m_parse.get_Index(), path);
    return (check);
}

void Server::location()
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
                    if ((check = locationContinued(i)) == 1)
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
        checkForTheIndex(this->m_parse.get_Index(), path);
        location();
        if (this->m_response.getType() == 0)
        {
            path += this->m_parse.getIndexToUse();
            m_response.contentHeader("200", "text", "html", readingTheFile(path));
            debug(m_response.getHeader());
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