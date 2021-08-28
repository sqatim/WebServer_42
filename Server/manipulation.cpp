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
    myReadFile.exceptions(std::ifstream::failbit);
    /* code */
    std::string text;
    std::string line;
    myReadFile.open(filename);
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
    int len;
    // m_response.header = affectationHeader("307 Temporary Redirect", "text", "html", m_response.body.length());
    // response = responseConcatenation(m_response.header, m_response.body);
    // if (parse.getlocation() != NULL)
    // {
    //     // ntsana amine hta ysali l3aybat
    // }
    if (this->m_content.root != "")
    {
        len = ft_strlen(this->m_content.root);
        if (this->m_content.root[len - 1] != '/')
            this->m_content.root += "/";
    }
    // hadi abash ntesti;
    this->m_content.index = "default.html";
    this->m_content.root += this->m_content.index;
    try
    {
        std::cout << this->m_content.root << std::endl;
        m_response.body = readingTheFile(this->m_content.root);
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "a sidi ra ghalta" << std::endl;
    }

    m_response.header = affectationHeader("200 OK", "text", "html", m_response.body.length());
    // if (m_response.body == "")
    // std::cout << "m_content.root ==> " << this->m_content.root << std::endl;
    response = responseConcatenation(m_response.header, m_response.body);
    // std::cout << "response ==> " << response << std::endl;
    send(socket, response.c_str(), response.length(), 0);
}