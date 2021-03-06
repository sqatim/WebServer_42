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
    Parse parse;

    if (!myReadFile)
        throw WebServer::Forbidden(parse, "");
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
void WebServer::manageRequest(int socket, int check, int request)
{
    std::string response;
    std::string root;
    LocaTion empty;
    Parse parse;
    try
    {
        root = getRoot(empty, this->m_parse, 0);
        slash(&root);
        if (request == -2)
            throw BadRequest(m_parse, root);
        if (this->m_request.getMethod() != "GET" && this->m_request.getMethod() != "POST" && this->m_request.getMethod() != "DELETE")
            throw MethodNotAllowed(m_parse, root);
        if (check == 0)
            throw NotFound(m_parse, root);
        else if (this->m_request.getMethod() == "GET")
            getMethod(socket);
        else if (this->m_request.getMethod() == "POST")
            postMethod(socket);
        else if (this->m_request.getMethod() == "DELETE")
            deleteMethod(socket);
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
    catch (WebServer::TooLarge &e)
    {
        m_response.toLargeBody(e.getParse(), e.getFileName());
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
    catch (WebServer::MethodNotAllowed &e)
    {
        m_response.methodNotAllowedBody(e.getParse(), e.getFileName());
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
    catch (WebServer::BadRequest &e)
    {
        m_response.badRequestBody(e.getParse(), e.getFileName());
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
}