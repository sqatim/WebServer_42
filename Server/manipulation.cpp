#include "WebServer.class.hpp"

int ft_strlen(std::string str)
{
    int i;

    i = 0;
    while (str.c_str()[i])
        i++;
    return (i);
}
std::string WebServer::readingTheFile(char *filename)
{

    std::ifstream myReadFile(filename);
    std::string text;
    std::string line;

    delete[] filename;
    if (!myReadFile)
        throw WebServer::Forbidden();
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
void WebServer::manageRequest(int socket)
{
    char *str;
    std::string response;
    // std::cout << this->m_request.getMethod() << std::endl;
    try
    {
        if (this->m_request.getMethod() == "GET")
            getMethod(socket);
        else if (this->m_request.getMethod() == "POST")
            postMethod(socket);
        else if (this->m_request.getMethod() == "DELETE")
            deleteMethod(socket);
        this->m_request.init();
    }
    catch (WebServer::Forbidden &e)
    {
        m_response.forbiddenBody(e.getParse(), e.getFileName());
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
    catch (WebServer::NotFound &e)
    {
        m_response.notFoundBody(e.getParse(), e.getFileName());
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
}