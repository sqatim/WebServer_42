#include "Server.class.hpp"

int ft_strlen(std::string str)
{
    int i;

    i = 0;
    while (str.c_str()[i])
        i++;
    return (i);
}
std::string readingTheFile(std::string filename)
{

    std::ifstream myReadFile;
    // https://www.cplusplus.com/reference/ios/ios/exceptions/
    // Get/set exceptions mask
    // failbit	Logical error on i/o operation	fail == true
    // myReadFile.exceptions(std::ifstream::badbit);
    /* code */
    std::string text;
    std::string line;
    std::cout << "==============================" << std::endl;
    std::cout << "Reading the file " << filename << std::endl;
    std::cout << "==============================" << std::endl;
    myReadFile.open(filename);
    if (!myReadFile)
        throw Server::Forbidden();
    text = "\0";
    while (std::getline(myReadFile, line))
    {
        text += line;
        if (!myReadFile.eof())
            text += "\n";
    }
    myReadFile.close();
    return (text);
}

void Server::manageRequest(std::string word, Parse parse, int socket)
{
    m_response.initResponse("HTTP/1.1", "Content-Type: ", "Content-Length: ");
    try
    {
        std::string path;
        int len;

        path = this->m_parse.getroot();
        this->m_parse.setIndex("index.html");
        if (path != "")
        {
            len = ft_strlen(path);
            if (path[len - 1] != '/')
                path += "/";
        }
        if (parse.getlocation().empty())
            ;
        else
        {
            if (word != "/")
            {
                for (int i = 0; i < parse.getlocation().size(); i++)
                {
                    if (word == parse.getlocation()[i].getname())
                    {
                        path += parse.getlocation()[i].getname();
                        if (parse.getlocation()[i].getindex() != "")
                            this->m_parse.setIndex(parse.getlocation()[i].getindex());
                    }
                    throw NotFound();
                }
            }
        }
        path += this->m_parse.getIndex();
        std::cout << path << std::endl;
        m_response.contentHeader("200 OK", "text", "html", readingTheFile(path));
        m_response.setHeader();
    }
    catch (Server::Forbidden &e)
    {
        std::cout << "salut mon camarade" << std::endl;
        m_response.forbiddenBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        m_response.setHeader();
    }
    catch (Server::NotFound &e)
    {
        m_response.notFoundBody();
        m_response.contentHeader(m_response.getStatus(), "text", "html", m_response.getBody());
        m_response.setHeader();
    }
    m_response.setResponse();
    // std::cout << "response ==> " << m_response.getResponse() << std::endl;
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}