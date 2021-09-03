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

void Server::checkForTheIndex(std::vector<std::string> index, std::string root)
{
    int len;
    std::ifstream indexFile;
    std::string path;
    if (index.size() == 0)
        this->m_parse.setIndexToUse("index.html");
    else
    {
        if (path != "")
        {
            len = ft_strlen(path);
            if (path[len - 1] != '/')
                path += "/";
        }
        for (int i = 0; i < index.size(); i++)
        {
            path = root + index[i];
            debug(path);
            indexFile.open(path);
            if (indexFile)
            {
                this->m_parse.setIndexToUse(index[i]);
                indexFile.close();
                return;
            }
            indexFile.close();
        }
    }
}
void Server::manageRequest(int socket)
{
    bool root = false;
    bool check = false;
    m_response.initResponse();
    try
    {
        std::string path = "";
        int len;

        path = this->m_parse.getroot();
        if (path == "")
        {
            path = "./Config";
        }
        if (path != "")
        {
            len = ft_strlen(path);
            if (path[len - 1] != '/')
                path += "/";
        }
        checkForTheIndex(this->m_parse.get_Index(), path);
        // debug(this->m_parse.getIndexToUse());
        if (this->m_parse.getlocation().empty())
            ;
        else
        {
            /**********************************************************************/
            /* khasni n9ad had l3ayba man ba3d mali nrtaaah ***********************/
            /**********************************************************************/
            // if (m_request.getPath() != "/")
            // {
            for(int i = 0; i < this->m_parse.getlocation().size(); i++)
            {
                if(this->m_parse.getlocation()[i].getname() == "/")
                    root = true;
            }
            for (int i = 0; i < this->m_parse.getlocation().size(); i++)
            {
                if (m_request.getPath() == this->m_parse.getlocation()[i].getname())
                {
                    if (this->m_parse.getlocation()[i].getroot() != "")
                    {
                        path = this->m_parse.getlocation()[i].getroot();
                        if (path != "")
                        {
                            len = ft_strlen(path);
                            if (path[len - 1] != '/')
                                path += "/";
                        }
                    }
                    path += this->m_parse.getlocation()[i].getname();
                    if (path != "")
                    {
                        len = ft_strlen(path);
                        if (path[len - 1] != '/')
                            path += "/";
                    }
                    if (this->m_parse.getlocation()[i].getindex().size() != 0)
                        checkForTheIndex(this->m_parse.getlocation()[i].getindex(), path);
                    else
                        checkForTheIndex(this->m_parse.get_Index(), path);
                }
                // throw NotFound();
            }
            // }
        }
        // debug(this->m_parse.getIndexToUse());
        path += this->m_parse.getIndexToUse();
        m_response.contentHeader("200 OK", "text", "html", readingTheFile(path));
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
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}