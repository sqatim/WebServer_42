#include "WebServer.class.hpp"

void WebServer::postMethodComparaison(int socket, size_t &i, std::string &locationName, int &check)
{
    std::string root;

    root = getRoot(m_parse.getlocation()[i], this->m_parse, 1);
    slash(&root);
    if (std::atoi(m_request.getContentLength().c_str()) / 1048576 > std::atoi(m_parse.getclient_max_body_size().c_str()))
        throw TooLarge(m_parse, root);
    locationName = &locationName[1];
    root.insert(root.length(), locationName);
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
    check = 1;
}

void WebServer::postMethod(int socket)
{
    m_response.initResponse();
    std::string locationName;
    std::vector<LocaTion> location;
    std::string url;

    int check = 0;
    url = m_request.getPath();
    while (true)
    {
        location = locationSorted(this->m_parse.getlocation());
        for (size_t i = 0; i < location.size(); i++)
        {
            locationName = location[i].getname();
            locationName = locationName.c_str();
            if (ft_comparaison(locationName.c_str(), url.c_str()))
            {
                postMethodComparaison(socket, i, locationName, check);
                break;
            }
        }
        if (check == 1)
            break;
        if (url == "/")
            break;
        lastSlash(url);
    }
}

int checkPermission(const char *path)
{
    struct stat fileStat;

    if (stat(path, &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IWOTH)
            return (1);
    }
    return (0);
}

void WebServer::deleteMethodComparaison(int socket, size_t &i)
{
    std::string url;
    std::string root;
    std::string path;

    url = getUrl(this->m_request);
    root = getRoot(this->m_parse.getlocation()[i], this->m_parse, 1);
    slash(&root);
    path = root;
    path.insert(path.length(), url.c_str());
    std::cout << path.c_str() << std::endl;
    if (fileOrDir(path.c_str()) == 1)
    {
        if (!checkPermission(path.c_str()))
            throw Forbidden(m_parse, root);
        m_response.fileDeleted();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
        remove(path.c_str());
    }
    else
        throw NotFound(m_parse, root);
}

void WebServer::deleteMethod(int socket)
{
    m_response.initResponse();
    std::string location;
    for (size_t i = 0; i < this->m_parse.getlocation().size(); i++)
    {
        location = this->m_parse.getlocation()[i].getname();
        location = location.c_str();
        if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
        {
            deleteMethodComparaison(socket, i);
            break;
        }
    }
}
void WebServer::getMethod(int socket)
{
    m_response.initResponse();
    std::string path;
    int check;
    std::string root;
    LocaTion empty;

    check = location(socket);
    if (check == -1)
    {
        root = getRoot(empty, this->m_parse, 0);
        slash(&root);
        if (getIndex(empty, m_parse, 0, root) == 1)
        {
            path = root.c_str();
            m_response.contentHeader("200", "text", "html", readingTheFile((char *)path.c_str()));
            this->m_response.sendResponse(socket);
        }
        else
            throw NotFound(m_parse, root);
    }
}
