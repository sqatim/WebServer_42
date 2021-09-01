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

    std::ifstream myReadFile("/Users/sqatim/Desktop/WebServer_42/form.html");
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
    // myReadFile.open(filename);
    // if (!myReadFile)
    // {
    // std::cout << myReadFile << std::endl;
    //     throw Server::Forbidden();
    // }
    text = "\0";
    while (std::getline(myReadFile, line))
    {
        text += line;
        if (!myReadFile.eof())
            text += "\n";
    }
    myReadFile.close();
    // std::cout << "text <<   " << text << std::endl;
    return (text);
}

void Server::manageRequest(Parse parse, int socket)
{
    m_response.initResponse();
    try
    {
        std::string path;
        int len;

        path = this->m_parse.getroot();
        std::cout << "[" << this->m_parse.getroot() << "]" << std::endl;

        this->debug(this->m_parse.get_Index()[0]);
        this->m_parse.setIndexToUse(this->m_parse.get_Index()[0]);
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
            if (m_request.getPath() != "/")
            {
                for (int i = 0; i < parse.getlocation().size(); i++)
                {
                    if (m_request.getPath() == parse.getlocation()[i].getname())
                    {
                        path += parse.getlocation()[i].getname();
                        if (parse.getlocation()[i].getindex()[0] != "")
                            this->m_parse.setIndexToUse(parse.getlocation()[i].getindex()[0]);
                    }
                    throw NotFound();
                }
            }
        }
        path += this->m_parse.getIndexToUse();
        m_response.contentHeader("200 OK", "text", "html", readingTheFile(path));
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
    m_response.setResponse();
    // std::cout << "response : " << m_response.getResponse() << std::endl;
    // std::cout << "response ==> " << m_response.getResponse() << std::endl;
    send(socket, m_response.getResponse().c_str(), m_response.getResponse().length(), 0);
}