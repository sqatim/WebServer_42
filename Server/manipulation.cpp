#include "WebServer.class.hpp"

char *ft_strjoin(char const *s1, char const *s2)
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

// int WebServer::checkForTheIndex(std::vector<std::string> index, std::string root, std::string &path)
// {
//     int len;
//     std::ifstream indexFile;
//     char *pathForTest;
//     // slash(&pathForTest);
//     if (index.size() == 0)
//     {
//         if (this->m_parse.getIndexToUse() == "")
//             this->m_parse.setIndexToUse("index.html");
//         slash(&root);
//         pathForTest = ft_strjoin(root.c_str(), "index.html");
//         indexFile.open(pathForTest);
//         delete pathForTest;
//         if (indexFile)
//         {
//             path = root;
//             indexFile.close();
//             return 1;
//         }
//         indexFile.close();
//         return (0);
//     }
//     else
//     {
//         slash(&root);
//         for (int i = 0; i < index.size(); i++)
//         {
//             pathForTest = ft_strjoin(root.c_str(), index[i].c_str());
//             indexFile.open(pathForTest);
//             delete pathForTest;
//             if (indexFile)
//             {
//                 this->m_parse.setIndexToUse(index[i]);
//                 path = root;
//                 indexFile.close();
//                 return 1;
//             }
//             indexFile.close();
//         }
//     }
//     return (0);
// }

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
    // std::cout << this->m_request.getMethod() << std::endl;
    if (this->m_request.getMethod() == "GET")
    {
        getMethod(socket);
    }
    else if (this->m_request.getMethod() == "POST")
    {
        str = strdup("/Users/sqatim/Desktop/WebServer_42/index.html");
        m_response.contentHeader("200", "text", "html", readingTheFile(str));
        m_response.sendResponse(socket);
        // std::cout << "POST" << std::endl;
    }
}