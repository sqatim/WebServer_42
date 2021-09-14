#include "WebServer.class.hpp"

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
            root = getRoot(parse.getlocation()[k], parse, 1);
            check = appendUrlCgi(k, root, parse.getlocation()[k]);
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
    std::cout << root << std::endl;
    if ((check = fileOrDir(root.c_str())) == 1)
    {
        path = strdup(root.c_str());
        m_response.contentHeader("200", "text", "html", readingTheFile(path));
        // std::cout << "It's a file" << std::endl;
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
        m_response.contentHeader("200", "text", "html", readingTheFile(path));
    }
    return (check);
}

int WebServer::whichLocation(Parse &parse, LocaTion location, std::string locationName, int socket)
{
    if (checkLocation(location) == 2)
    {
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

int WebServer::location(int socket)
{
    int check;
    int check1;
    std::string location;
    std::string root;

    check = -1;
    check1 = -1;
    if ((check = fastCgi(m_request, m_parse, root)) == 1)
    {
        std::cout << "fast cgi" << std::endl;
        exit(0);
    }
    if (check == -1 || check == 2)
    {

        for (int i = 0; i < this->m_parse.getlocation().size(); i++)
        {
            location = this->m_parse.getlocation()[i].getname();
            location = location.c_str();
            // std::cout << "normalement" << std::endl;
            if (ft_comparaison(location.c_str(), m_request.getPath().c_str()))
            {
                if ((check = whichLocation(m_parse, m_parse.getlocation()[i], location, socket)) == 1)
                {
                    check1 = 1;
                    this->m_response.sendResponse(socket);
                    return 1;
                }
            }
        }
    }
    if (check == 0)
        throw NotFound();
    return (check1);
}