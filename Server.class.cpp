#include "Server.class.hpp"

Server::Server()
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
    if ((this->m_socketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::string("Socket Failed To Create");
    initialiseStructure();
    /**************************************************************************/
    /* int bind(int sockfd, const struct sockaddr *addr), socklen_t addrlen); */
    /*                                                                        */
    /*   # after Creation of the socket, bind function binds the socket to    */
    /* the adress and port number specified in addr (costum data structure)   */
    /**************************************************************************/
    if ((bind(this->m_socketFd, (struct sockaddr *)&this->m_address, sizeof(this->m_address))) < 0)
        throw std::string("Bind Failed");
}

void Server::initialiseStructure()
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
    this->m_address.sin_family = AF_INET;
    this->m_address.sin_port = htons(PORT);
    this->m_address.sin_addr.s_addr = INADDR_ANY;
    return;
}

void Server::manipulation()
{
    // to delete
    int fd = open("index.html", O_RDWR);
    char *html = new char[5000000];
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
    if ((listen(this->m_socketFd, 5)) < 0)
        throw std::string("Listen Failed");
    if ((m_newSocket = accept(this->m_socketFd, (struct sockaddr *)&this->m_address, (socklen_t *)&this->m_address)) < 0)
        throw std::string("Accept Failed");
    char buffer[30000] = {0};
    read(this->m_newSocket, buffer, 30000);
    read(fd, html, 5000000);
    printf("%s\n", buffer);
    write(this->m_newSocket, html, 5000000);
    delete[] html;
}

int Server::getSocketFd()
{
    return (this->m_socketFd);
}

Server::~Server()
{
    return;
}