#ifndef SERVER_CLASS_HPP
#define SERVER_CLASS_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
// 7ta nshuf blanhum man ba3d
#include <unistd.h>
#include <fcntl.h>

#define PORT 80
class Server
{
private:
    int m_socketFd;
    int m_newSocket;
    struct sockaddr_in m_address;
public:
    Server(/* args */);
    int getSocketFd();
    struct sockaddr_in getAddress();
    void initialiseStructure(void);
    void manipulation();
    ~Server();
};


#endif