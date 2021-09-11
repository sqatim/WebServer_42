#include "Server.class.hpp"

static std::string ft_joinSlash(char **array, const char *path)
{
    std::string str = "";
    int len;
    for (int i = 0; array[i]; i++)
    {
        len = ft_strlen(str.c_str());
        str.insert(len, array[i]);
        len = ft_strlen(str.c_str());
        if (array[i + 1] || path[ft_strlen(path) - 1] == '/')
            str.insert(len, "/");
    }
    return (str.c_str());
}

static char *ft_strjoin(char const *s1, char const *s2)
{
    char *p;
    size_t i;
    size_t j;
    size_t k;

    i = 0;
    j = 0;
    k = 0;
    if (s1 && s2)
    {
        p = new char[sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)];
        if (p == NULL)
            return (NULL);
        while (s1[j])
        {
            p[i++] = s1[j++];
        }
        while (s2[k])
        {
            p[i++] = s2[k++];
        }
        p[i] = '\0';
        return (p);
    }
    return (NULL);
}

static void slash(std::string *path)
{
    int len;
    if (*path != "")
    {
        len = ft_strlen(path->c_str());
        if ((*path)[len - 1] != '/')
            path->insert(len, "/");
    }
}

static int ft_comparaison(std::string location, std::string uri)
{
    int i;

    for (i = 0; location.c_str()[i]; i++)
    {
        if (i == 0 && (location.c_str()[0] == '/' && uri.c_str()[0] == '/'))
            i++;
        if (location.c_str()[i] == '/' && location.c_str()[i + 1] == '\0')
            break;
        if (location[i] != uri[i] || (location.c_str()[i] == '/' && location.c_str()[i + 1] == '/'))
            return (0);
    }
    return (1);
}


void Server::getMethod(int socket)
{
    m_response.initResponse();
    try
    {
        std::string path = "";
        int len;
        char *result;
        path = this->m_parse.getroot();
        if (path == "")
            path = "./Config";
        slash(&path);
        checkForTheIndex(this->m_parse.get_Index(), path, path);
        // exit(0);
        location(socket, path);
        if (this->m_response.getType() == 0 || this->m_response.getType() == 2)
        {
            if (this->m_response.getType() == 0)
            {
                result = ft_strjoin(path.c_str(), this->m_parse.getIndexToUse().c_str());
                m_response.contentHeader("200", "text", "html", readingTheFile(result));
            }
            else
            {
                result = strdup(path.c_str());
                m_response.contentHeader("200", "text", "html", readingTheFile(result));
            }
        }
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
    // debug(this->m_response.getHeader());
    // this->m_response.getStatus();
    m_response.setResponse();
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}
