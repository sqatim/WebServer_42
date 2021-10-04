#include "WebServer.class.hpp"
#include "../Parsing/cgi.hpp"

void lastSlash(std::string &string)
{
    int counter;

    counter = 0;
    for (size_t i = 0; i < string.size(); i++)
    {
        if (string[i] == '/')
            counter = i;
    }
    if (counter == 0)
        string = "/";
    else
        string = string.substr(0, counter);
}

std::vector<LocaTion> locationSorted(std::vector<LocaTion> location)
{
    std::string string;
    std::vector<LocaTion> locationSorted;
    size_t len;
    int save;

    save = 0;
    len = 0;
    for (int counter = location.size() - 1; counter >= 0; counter--)
    {
        len = 0;
        for (size_t i = 0; i < location.size(); i++)
        {
            if (location[i].getname().size() > len)
            {
                len = location[i].getname().size();
                save = i;
            }
        }
        locationSorted.push_back(location[save]);
        location.erase(location.begin() + save);
    }
    return (locationSorted);
}

int fastCgi(Request &request, Parse &parse, std::string &root, LocaTion &location)
{
    int cgi;
    int check;

    check = -1;

    if ((cgi = ft_cgi(request.getPath().c_str()) == 1) ||
        (cgi = ft_cgi(request.getPath().c_str()) == 2))
    {

        size_t k = 0;
        if (cgi == 1)
            while (parse.getlocation()[k].getname() != "*.php" &&
                   k < parse.getlocation().size())
                k++;
        else
            while (parse.getlocation()[k].getname() != "*.py" &&
                   k < parse.getlocation().size())
                k++;
        if (parse.getlocation()[k].getname() == "*.php" ||
            parse.getlocation()[k].getname() == "*.py")
        {
            location = parse.getlocation()[k];
            root = getRoot(parse.getlocation()[k], parse, 1);
            check = appendUrlCgi(root, parse.getlocation()[k], request.getPath().c_str());
        }
    }
    return (check);
}

int WebServer::theRestOfAppendLocation(LocaTion &location, std::string &url, std::string &root, int &check)
{
    std::string body;
    std::string path;

    slash(&root);
    if ((check = getIndex(location, m_parse, 1, root)) == 0)
    {

        if (location.getauto_index() == "on" && fileOrDir(root.c_str()) == 2)
        {
            body = this->m_response.autoIndexBody(root.c_str(), url.c_str());
            m_response.contentHeader("200", "text", "html", body);
            return (1);
        }
    }
    else
    {
        path = root.c_str();
        m_response.contentHeader("200", "text", "html", readingTheFile((char *)path.c_str()));
    }
    return (check);
}

int WebServer::appendLocation(LocaTion location)
{
    std::string root;
    int check = 0;
    std::string url;
    std::string path;

    url = getUrl(this->m_request);
    root = getRoot(location, this->m_parse, 1);
    slash(&root);
    if (location.get_GET() != 1)
        throw MethodNotAllowed(m_parse, root);
    root.insert(root.length(), url.c_str());
    if ((check = fileOrDir(root.c_str())) == 1)
    {
        path = root.c_str();
        m_response.contentHeader("200", "text", "html", readingTheFile((char *)path.c_str()));
        return (1);
    }
    if (root[root.length() - 1] != '/' && check == 2)
    {
        m_response.redirectHeaderToPath("301", m_request.getHost(), url);
        return (2);
    }
    return (theRestOfAppendLocation(location, url, root, check));
}

int WebServer::whichLocation(LocaTion location)
{

    if (checkLocation(location) == 2)
    {
        this->m_response.redirectHeader(location.get_return()[0].redirec, location.get_return()[0].path);
        return (1);
    }
    else if ((appendLocation(location)) != 0)
    {
        return (1);
    }
    return (0);
}

int checkForSlashLocation(std::vector<LocaTion> &location)
{
    for (size_t i = 0; i < location.size(); i++)
    {
        if (location[i].getname() == "/")
            return (1);
    }
    return (0);
}

int WebServer::CheckingForCgi(int socket)
{
    std::string root;
    LocaTion locationCgi;

    if (fastCgi(m_request, m_parse, root, locationCgi) == 1)
    {

        if (locationCgi.get_GET() != 1)
        {
            lastSlash(root);
            throw MethodNotAllowed(m_parse, root);
        }
        this->m_request.setFastCgi(locationCgi.getfascgi_pass());
        CGI cg;
        cg.set_value_to_maymap(m_request);
        cg.execute(root, m_request.getFastCgi());
        m_response.contentHeader("200", "text", "html", cg.get_outpout());
        m_response.sendResponse(socket);
        return (1);
    }
    return (0);
}

int WebServer::checkingForTheRightLocation(LocaTion &location, std::string &url, int &check, int socket)
{
    std::string locationName;
    LocaTion empty;
    locationName = location.getname();
    locationName = locationName.c_str();
    std::string error;

    error = getRoot(empty, m_parse, 0);
    slash(&error);
    if (ft_comparaison(locationName.c_str(), url.c_str()))
    {
        if ((check = whichLocation(location)) == 1)
        {
            this->m_response.sendResponse(socket);
            return 1;
        }
        else
            throw Forbidden(m_parse, error);
    }
    return (0);
}

int WebServer::location(int socket)
{
    int check;
    std::vector<LocaTion> location;
    LocaTion empty;
    std::string url;
    std::string root;

    root = getRoot(empty, m_parse, 0);
    slash(&root);
    check = -1;
    if (CheckingForCgi(socket) == 1)
    {
        return (1);
    }
    if (check == -1 || check == 2)
    {
        url = m_request.getPath();
        location = locationSorted(this->m_parse.getlocation());
        while (true)
        {
            for (size_t i = 0; i < location.size(); i++)
            {
                if (checkingForTheRightLocation(location[i], url, check, socket) == 1)
                    return (1);
            }
            if (url == "/")
                break;
            lastSlash(url);
        }
        if (m_request.getPath() != "/" && this->m_parse.getlocation().size() != 0)
            check = 0;
    }
    if (check == 0)
        throw NotFound(m_parse, root);
    return (-1);
}