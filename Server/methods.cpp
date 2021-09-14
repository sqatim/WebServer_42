#include "Server.class.hpp"

void Server::getMethod(int socket)
{
    m_response.initResponse();
    try
    {
        char *path;
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
                std::cout << "root: " << root << std::endl;
                path = strdup(root.c_str());
                m_response.contentHeader("200", "text", "html", readingTheFile(path));
                this->m_response.sendResponse(socket);
            }
            else
                throw NotFound();
        }
    }
    catch (Server::Forbidden &e)
    {
        m_response.forbiddenBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
    catch (Server::NotFound &e)
    {
        m_response.notFoundBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        this->m_response.sendResponse(socket);
    }
}
