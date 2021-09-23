#include "WebServer.class.hpp"

void lastSlash(std::string &string)
{
    int counter = 0;

    for (int i = 0; i < string.size(); i++)
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
    int len = 0;
    int save = 0;
    for (int counter = location.size() - 1; counter >= 0; counter--)
    {
        len = 0;
        for (int i = 0; i < location.size(); i++)
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

int fastCgi(Request &request, Parse &parse, std::string &root)
{
    int cgi;
    int check;

    check = -1;
    if ((cgi = ft_cgi(request.getPath().c_str()) == 1) || (cgi = ft_cgi(request.getPath().c_str()) == 2))
    {
        int k = 0;
        if (cgi == 1)
            while (parse.getlocation()[k].getname() != "*.php" && k < parse.getlocation().size())
                k++;
        else
            while (parse.getlocation()[k].getname() != "*.py" && k < parse.getlocation().size())
                k++;
        if (parse.getlocation()[k].getname() == "*.php" || parse.getlocation()[k].getname() == "*.py")
        {
            // std::cout << request.getPath().c_str() << std::endl;
            root = getRoot(parse.getlocation()[k], parse, 1);
            std::cout << "root ==> " << root << std::endl;
            check = appendUrlCgi(k, root, parse.getlocation()[k], request.getPath().c_str());
        }
    }
    return (check);
}

int WebServer::appendLocation(LocaTion location, int socket)
{
    std::string root;
    int check = 0;
    std::string url;
    std::string body;
    char *path;

    url = getUrl(this->m_request);
    root = getRoot(location, this->m_parse, 1);
    slash(&root);
    root.insert(root.length(), url.c_str());
    // std::cout << root.c_str() << std::endl;
    if ((check = fileOrDir(root.c_str())) == 1)
    {
        path = strdup(root.c_str());
        m_response.contentHeader("200", "text", "html", readingTheFile(path));
        return (1);
    }
    if (root[root.length() - 1] != '/' && check == 2)
    {
        m_response.redirectHeaderToPath(socket, "301", m_request.getHost(), url);
        return (2);
    }
    slash(&root);
    if ((check = getIndex(location, m_parse, 1, root)) == 0)
    {

        if (location.getauto_index() == "on" && fileOrDir(root.c_str()) == 2)
        {
            // std::cout << "****************** samir ******************\n"
            //           << root << " [" << check << "]" << std::endl;
            body = this->m_response.autoIndexBody(root.c_str(), url.c_str());
            // std::cout << body << std::endl;
            m_response.contentHeader("200", "text", "html", body);
            return (1);
        }
    }
    else
    {
        path = strdup(root.c_str());
        std::cout << "i am here" << std::endl;
        m_response.contentHeader("200", "text", "html", readingTheFile(path));
    }
    return (check);
}

int WebServer::whichLocation(Parse &parse, LocaTion location, std::string locationName, int socket)
{
    if (checkLocation(location) == 2)
    {
        std::cout << "sasa yasoso" << std::endl;
        this->m_response.redirectHeader(socket, location.get_return()[0].redirec,
                                        location.get_return()[0].path);
        return (1);
    }
    else if ((appendLocation(location, socket)) != 0)
        return (1);
    // else
    // return (-1);
    return (0);
}

int checkForSlashLocation(std::vector<LocaTion> &location)
{
    for (int i = 0; i < location.size(); i++)
    {
        if (location[i].getname() == "/")
            return (1);
    }
    return (0);
}
int WebServer::location(int socket)
{
    int check;
    int check1;
    std::string locationName;
    std::string root;
    std::vector<LocaTion> location;
    std::string url;

    check = -1;
    check1 = -1;
    if ((check = fastCgi(m_request, m_parse, root)) == 1)
    {

        // std::cout << "fast cgi" << std::endl;
        exit(0);
    }

    if (check == -1 || check == 2)
    {
        // std::cout << "location: " << this->m_parse.getlocation().size() << std::endl;
        url = m_request.getPath();
        while (true)
        {
            location = locationSorted(this->m_parse.getlocation());
            for (int i = 0; i < location.size(); i++)
            {
                locationName = location[i].getname();
                locationName = locationName.c_str();
                if (ft_comparaison(locationName.c_str(), url.c_str()))
                {
                    if ((check = whichLocation(m_parse, location[i], locationName, socket)) == 1)
                    {
                        check1 = 1;
                        this->m_response.sendResponse(socket);
                        return 1;
                    }
                }
            }
            if (check == 1)
                break;
            if (url == "/")
                break;
            lastSlash(url);
        }
        if (m_request.getPath() != "/" && this->m_parse.getlocation().size() != 0)
            check = 0;
    }
    if (check == 0)
        throw NotFound();
    return (check1);
}