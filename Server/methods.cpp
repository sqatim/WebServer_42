#include "WebServer.class.hpp"

void WebServer::postMethod(int socket)
{
    m_response.initResponse();
    char *path;
    std::string root;
    std::string locationName;
    std::vector<LocaTion> location;
    std::string response;
    std::string url;

    int check = 0;
    url = m_request.getPath();
    std::cout << "[" << std::atoi(m_request.getContentLength().c_str()) / 1048576 << "]" << std::endl;
    while (true)
    {
        location = locationSorted(this->m_parse.getlocation());
        for (int i = 0; i < location.size(); i++)
        {
            locationName = location[i].getname();
            locationName = locationName.c_str();
            if (ft_comparaison(locationName.c_str(), url.c_str()))
            {
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
        if (fileStat.st_mode & S_IROTH)
        {
            std::cout << "kayna" << std::endl;
            return (1);
        }
        else
            std::cout << "ma kaynsh" << std::endl;
    }
    return (0);
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
                if (!checkPermission(path.c_str()))
                    throw Forbidden(m_parse, root);
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
