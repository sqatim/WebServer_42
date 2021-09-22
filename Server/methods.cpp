#include "WebServer.class.hpp"

void WebServer::postMethod(int socket)
{
    m_response.initResponse();
    char *path;
    std::string root;
    std::string location;
    std::string response;

    for (int i = 0; i < this->m_parse.getlocation().size(); i++)
    {
        location = this->m_parse.getlocation()[i].getname();
        location = location.c_str();
        if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
        {
            root = getRoot(m_parse.getlocation()[i], this->m_parse, 1);
            slash(&root);
            location = &location[1];
            root.insert(root.length(), location);
            slash(&root);
            root.insert(root.length(), this->m_parse.getlocation()[i].getupload_store());
            slash(&root);
            if (fileOrDir(root.c_str()) == 2)
                this->m_request.uploadInFile(root.c_str());
            else
                throw NotFound();
            m_response.fileUploaded();
            m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
            this->m_response.sendResponse(socket);
            break;
        }
    }
}

void WebServer::deleteMethod(int socket)
{
    m_response.initResponse();
    int check;
    std::string root;
    LocaTion empty;
    std::string location;
    std::string path;
    // char *response = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\nContent-Length: 5\n\nsamir";
    std::string url;
    // check = location(socket);
    std::cout << this->m_parse.getlocation().size() << std::endl;
    for (int i = 0; i < this->m_parse.getlocation().size(); i++)
    {
        location = this->m_parse.getlocation()[i].getname();
        location = location.c_str();
        if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
        {
            url = getUrl(this->m_request);
            root = getRoot(this->m_parse.getlocation()[i], this->m_parse, 1);
            slash(&root);
            path = root;
            path.insert(path.length(), url.c_str());
            std::cout << path.c_str() << std::endl;
            if ((check = fileOrDir(path.c_str())) == 1)
            {
                m_response.fileDeleted();
                m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
                this->m_response.sendResponse(socket);
                remove(path.c_str());
                break;
            }
            else
                throw NotFound(m_parse, root);
        }
    }
}
void WebServer::getMethod(int socket)
{
    m_response.initResponse();
    char *path;
    int check;
    std::string root;
    LocaTion empty;

    check = location(socket);
    if (check == -1)
    {
        // std::cout << "e*****************wa ya saide*****************" << std::endl;
        root = getRoot(empty, this->m_parse, 0);
        slash(&root);
        // debug(root);
        if (getIndex(empty, m_parse, 0, root) == 1)
        {
            path = strdup(root.c_str());
            m_response.contentHeader("200", "text", "html", readingTheFile(path));
            this->m_response.sendResponse(socket);
        }
        else
            throw NotFound(m_parse, root);
    }
}
