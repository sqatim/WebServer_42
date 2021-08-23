#include "Server.class.hpp"
#define PORT 3000

Server::Server(Parse parse) : m_maxFd(10), m_addrlen(sizeof(m_address))
{
    /**************************************************************************/
    /* int socket(int domain, int type, int protocol);                        */
    /*                                                                        */
    /* crée un point de communication, et renvoie un descripteur.             */
    /* # domain   : AF_INET / AF_INET6                                        */
    /* # type     :                                                           */
    /*     - SOCKE_STREAM : reliable(fiable) byte stream(i.e TCP)             */
    /*     - SOCKE_DGRAM : unreliable datagrams(i.e UDP)                      */
    /* # protocol :                                                           */
    /*     - 0 : use default based on domain and type                         */
    /*     - IPROTO_TCP : TCP                                                 */
    /*     - IPROTO_UDP : UCP                                                 */
    /**************************************************************************/
    this->m_socketFd = new int;
    if ((this->m_socketFd[0] = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::string("Socket Failed To Create");
    initialiseStructure(parse);
    /**************************************************************************/
    /* int bind(int sockfd, const struct sockaddr *addr), socklen_t addrlen); */
    /*                                                                        */
    /*   # after Creation of the socket, bind function binds the socket to    */
    /* the adress and port number specified in addr (costum data structure)   */
    /**************************************************************************/
    if ((bind(this->m_socketFd[0], (struct sockaddr *)&this->m_address, sizeof(this->m_address))) < 0)
        throw std::string("Bind Failed");
    std::cout << "Listener on port " << parse.getlisten()[0] << std::endl;
    if ((listen(this->m_socketFd[0], 3)) < 0)
        throw std::string("Listen Failed");
    std::cout << "Waiting for connections ..." << std::endl;
}
void checkListen(std::string listenParse, std::string **listen)
{
    int check;

    check = 1;
    for (int i = 0; listenParse.c_str()[i]; i++)
    {
        if (listenParse.c_str()[i] == ':')
            check = 2;
    }
    if (check == 1)
    {
        // std::cout << "Port bohdo" << std::endl;
        (*listen)[0] = "0.0.0.0";
        (*listen)[1] = listenParse;
    }
    if (check == 2)
    {
        // std::cout << "bjuj" << std::endl;
        int i;
        (*listen)[0] = "";
        for (i = 0; listenParse.c_str()[i] != ':'; i++)
        {
            (*listen)[0] += listenParse.c_str()[i];
        }
        (*listen)[0][i] = '\0';
        (*listen)[1] = "";
        for (i = i + 1; listenParse.c_str()[i] != ';'; i++)
        {
            (*listen)[1] += listenParse.c_str()[i];
            // std::cout << listenParse.c_str()[i] << std::endl;
        }
        (*listen)[1][i] = '\0';
    }
    return;
}
void function(std::vector<std::string> listenParse, std::string *listen)
{
    // akantesti bhad condition
    if (!isdigit(listenParse[0][0]))
    {
        // std::cout << "ghalta a weld 3amu" << std::endl;
        listen[0] = "0.0.0.0";
        listen[0] = "80";
    }
    checkListen(listenParse[0], &listen);
}
void Server::initialiseStructure(Parse parse)
{
    std::string listen[2];
    int port;
    /**************************************************************************/
    /* struct SOCKADDR_IN{short sin_family; u_short sin_port;\                */
    /*        struct in_addr sin_addr; char sin_zero[0]; };                   */
    /*                                                                        */
    /* struct in_addr{unsigned long s_addr; }                                 */
    /*                                                                        */
    /* # sin_family : Specifies the adress family, usualy the constant \      */
    /*         "AF_INET"                                                      */
    /* # sin_port   : Specifies the port number and must to be used with      */
    /*           htons() function which converts the "host byte order" to     */
    /*           "network byte order" so it can be transmited and routed      */
    /*           properly when opening the socket connection. the reason for  */
    /*           this is that computers and network protocols order their     */
    /*           bytes in a non-compatible fashion, each the opposite of      */
    /*           the other                                                    */
    /* # sin_addr   : holds the IP adress returned by inet_addr() to be used  */
    /*           in the socket connection                                     */
    /* # siz_zero   : usualy set to 0                                         */
    /**************************************************************************/
    function(parse.getlisten(), listen);
    // std::cout << listen[0].c_str() << std::endl;
    // std::cout << " stoi port " << stoi(listen[1]) << std::endl;
    // port = (uint16_t)stoi(parse.getlisten()[0]);
    this->m_address.sin_family = AF_INET;
    port = stoi(listen[1]);
    this->m_address.sin_port = htons(port);
    this->m_address.sin_addr.s_addr = inet_addr(listen[0].c_str());
    // this->m_address.sin_addr.s_addr = INADDR_ANY;
    return;
}

std::string readingTheFile(std::string filename)
{
    std::ifstream myReadFile(filename);
    std::string text;
    std::string line;

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

int Server::checkForFileDescriptor(int current)
{
    // count number of listen to insert here <3
    for (int i = 0; i < 1; i++)
    {
        if (current == this->m_socketFd[i])
            return (1);
    }
    return (0);
}
void Server::manipulation()
{
    // to delete
    std::string response;
    int result;
    std::string file;
    std::string ss = "\0";
    fd_set readySockets;
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int i = 0;
    int max_listen = 1;

    m_response.body = readingTheFile("index.html");
    m_response.header = affectationHeader("200 OK", "text", "html", m_response.body.length());
    response = responseConcatenation(m_response.header, m_response.body);
    /**************************************************************************/
    /* int listen(int sockfd, int backlog)                                    */
    /*                                                                        */
    /* # it puts the server socket in a passive mode, where it waits for      */
    /*  the client to approach the server to make a connection.               */
    /*                                                                        */
    /*   the backlog, defines the maximum lenght to which the queue of        */
    /*  pending connections for sockfd may grow.                              */
    /*                                                                        */
    /*    if a connection request arrives when the queue is full/             */
    /*  the client may receive an error with an indication of ECONNREFUSED.   */
    /**************************************************************************/
    FD_ZERO(&this->m_currentSocket);
    this->m_maxFd = this->m_socketFd[0];
    while (1)
    {
        // here i need to change 1 with the number of listen
        for (int k = 0; k < 1; k++)
            FD_SET(this->m_socketFd[0], &this->m_currentSocket);
        readySockets = this->m_currentSocket;
        std::string request;
        if (select(this->m_maxFd + 1, &this->m_currentSocket, NULL, NULL, NULL) < 0)
            throw std::string("mushkil f select");
        for (int i = 0; i <= this->m_maxFd; i++)
        {
            if (FD_ISSET(i, &this->m_currentSocket))
            {
                if (checkForFileDescriptor(i))
                {
                    std::cout << "i  ==> " << i << std::endl;
                    if ((m_newSocket = accept(i, (struct sockaddr *)&this->m_address, (socklen_t *)&this->m_addrlen)) < 0)
                        throw std::string("Accept Failed");
                    // hta nzid shi hwayj man ba3d
                    std::cout << "New connection, socket fd is : " << this->m_newSocket << std::endl;
                    FD_SET(this->m_newSocket, &this->m_currentSocket);
                    std::cout << "Adding to list of sockets as " << this->m_newSocket << std::endl;
                    if (this->m_newSocket > this->m_maxFd)
                        this->m_maxFd = this->m_newSocket;
                }
                else
                {
                    std::cout << "client_socket " << i << std::endl;
                    char buffer[1024] = {0};
                    if ((result = read(i, buffer, 1024)) == 0)
                    {
                        std::cout << "disconnected" << std::endl;
                    }
                    else
                    {
                        buffer[result] = '\0';
                        std::cout << getWord(buffer, 0, 1) << std::endl;
                        send(i, response.c_str(), response.length(), 0);
                    }
                    close(i);
                    FD_CLR(i, &this->m_currentSocket);
                }
            }
        }
    }
}

int Server::getSocketFd()
{
    return (this->m_socketFd[0]);
}

Server::~Server()
{
    return;
}