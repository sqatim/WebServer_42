#include "Server.class.hpp"
#define PORT 3000
// #undef __FD_SETSIZE
// #define __FD_SETSIZE 11264

Server::Server(Parse parse, int &maxSocket, std::vector<int> &servers, struct sockaddr_in &address) : m_addrlen(sizeof(m_address))
{
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
    size_t i;

    for (i = 0; i < parse.getlisten().size(); i++)
    {
        if ((m_socketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
            throw std::string("Socket Failed To Create");
        if (setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                       sizeof(opt)) < 0)
        {
            throw std::string("SetSockopt Failed");
        }
        initialiseStructure(parse.getlisten()[i], parse.gethost(), address);
        /**************************************************************************/
        /* int bind(int sockfd, const struct sockaddr *addr), socklen_t addrlen); */
        /*                                                                        */
        /*   # after Creation of the socket, bind function binds the socket to    */
        /* the adress and port number specified in addr (costum data structure)   */
        /**************************************************************************/
        if ((bind(m_socketFd, (struct sockaddr *)&this->m_address, sizeof(this->m_address))) < 0)
            throw std::string("Bind Failed");
        std::cout << "Listener on " << parse.gethost() << ":" << parse.getlisten()[i] << std::endl;
        if ((listen(m_socketFd, 10)) < 0)
            throw std::string("Listen Failed");
        servers.push_back(m_socketFd);
    }
    maxSocket += i - 1;
}

void Server::initialiseStructure(int port, std::string ip, struct sockaddr_in &address)
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
    address = this->m_address;
    return;
}

Server::~Server()
{
    return;
}
