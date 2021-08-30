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
    std::string response;
    try
    {
        std::string path;
        int len;

        path = this->m_content.root;
        this->m_content.index = "index.html";
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
                            this->m_content.index = parse.getlocation()[i].getindex();
                    }
                    throw NotFound();
                }
            }
        }
        path += this->m_content.index;
        std::cout << path << std::endl;
        m_response.body = readingTheFile(path);
        m_response.header = affectationHeader("200 OK", "text", "html", m_response.body.length());
    }
    catch (Server::Forbidden &e)
    {
        std::cout << "salut mon camarade" << std::endl;
        m_response.header = affectationHeader(e.forbiddenBody(m_response.body), "text", "html", m_response.body.length());
    }
    catch (Server::NotFound &e)
    {
        m_response.header = affectationHeader(e.notFoundBody(m_response.body), "text", "html", m_response.body.length());
    }
    response = responseConcatenation(m_response.header, m_response.body);
    // std::cout << "response ==> " << response << std::endl;
    send(socket, response.c_str(), response.length(), 0);
}