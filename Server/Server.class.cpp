#include "Server.class.hpp"
#define PORT 3000

Server::Server(Parse parse) : m_maxFd(10), m_addrlen(sizeof(m_address))
{
    this->m_content.root = parse.getroot();
    this->m_content.index = "default.html";
    int opt = 1;
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
    int i;
    this->m_socketFd = new int[parse.getlisten().size()];
    for (i = 0; i < parse.getlisten().size(); i++)
    {
        if ((this->m_socketFd[i] = socket(AF_INET, SOCK_STREAM, 0)) == 0)
            throw std::string("Socket Failed To Create");
        if (setsockopt(this->m_socketFd[i], SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                       sizeof(opt)) < 0)
        {
            throw std::string("SetSockopt Failed");
        }
        initialiseStructure(parse.getlisten()[i], parse.gethost());
        /**************************************************************************/
        /* int bind(int sockfd, const struct sockaddr *addr), socklen_t addrlen); */
        /*                                                                        */
        /*   # after Creation of the socket, bind function binds the socket to    */
        /* the adress and port number specified in addr (costum data structure)   */
        /**************************************************************************/
        if ((bind(this->m_socketFd[i], (struct sockaddr *)&this->m_address, sizeof(this->m_address))) < 0)
            throw std::string("Bind Failed");
        std::cout << "Listener on " << parse.gethost() << ":" << parse.getlisten()[i] << std::endl;
        if ((listen(this->m_socketFd[i], 3)) < 0)
            throw std::string("Listen Failed");
    }
    this->m_maxFd = this->m_socketFd[i - 1];
}

void Server::initialiseStructure(int port, std::string ip)
{
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
    std::cout << "port " << port << std::endl;
    this->m_address.sin_family = AF_INET;
    this->m_address.sin_port = htons(port);
    this->m_address.sin_addr.s_addr = inet_addr(ip.c_str());
    return;
}

int Server::checkForFileDescriptor(int current, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (current == this->m_socketFd[i])
            return (1);
    }
    return (0);
}
void Server::manipulation(Parse parse)
{
    // to delete
    std::string response;
    std::string word;
    int result;
    std::string file;
    std::string ss = "\0";
    fd_set readySockets;
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int i = 0;
    int max_listen = 1;

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
    std::cout << "Waiting for connections ..." << std::endl;
    std::cout << "=====================================" << std::endl;
    for (int i = 0; i < parse.getlisten().size(); i++)
        FD_SET(this->m_socketFd[i], &this->m_currentSocket);
    while (1)
    {
        readySockets = this->m_currentSocket;
        std::string request;
        if (select(this->m_maxFd + 1, &readySockets, NULL, NULL, NULL) < 0)
            throw std::string("mushkil f select");
        for (int i = 0; i <= this->m_maxFd; i++)
        {
            if (FD_ISSET(i, &readySockets))
            {
                if (checkForFileDescriptor(i, parse.getlisten().size()))
                {
                    std::cout << "i ==> " << i << std::endl;
                    if ((m_newSocket = accept(i, (struct sockaddr *)&this->m_address, (socklen_t *)&this->m_addrlen)) < 0)
                        throw std::string("Accept Failed");
                    std::cout << "New connection, socket fd is : " << this->m_newSocket << std::endl;
                    FD_SET(this->m_newSocket, &readySockets);
                    std::cout << "Adding to list of sockets as " << this->m_newSocket << std::endl;
                    if (this->m_newSocket > this->m_maxFd)
                        this->m_maxFd = this->m_newSocket;
                }
                else
                {
                    std::cout << "client_socket " << i << std::endl;
                    char buffer[1024] = {0};
                    if ((result = read(i, buffer, 1024)) == 0)
                        std::cout << "disconnected" << std::endl;
                    else
                    {
                        buffer[result] = '\0';
                        word = getWord(buffer, 0, 1);
                        manageRequest(word, parse, i);
                        printf("%s\n", buffer);
                        // std::cout << getWord(buffer, 0, 1) << std::endl;
                    }
                    close(i);
                    FD_CLR(i, &readySockets);
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