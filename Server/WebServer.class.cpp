#include "WebServer.class.hpp"

WebServer::WebServer(WebServ &webServ) : m_maxSocket(0), m_addrlen(sizeof(m_address)), m_webServ(webServ)
{
    // m_webServ = webServ;
}

Server WebServer::setServer(Parse &parse)
{
    Server server(parse, m_maxSocket, m_server, m_address);
    return server;
}

void WebServer::run()
{
    int i;
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
    std::cout << "Waiting for connections ..." << std::endl;
    std::cout << "=====================================" << std::endl;
    int sd;
    // for (int i = 0; i < this->m_parse.getlisten().size(); i++)
    while (1)
    {
        FD_ZERO(&this->m_currentSocket);
        for (i = 0; i < this->m_server.size(); i++)
        {
            FD_SET(this->m_server[i], &this->m_currentSocket);
            this->m_maxFd = this->m_server[i];
        }
        // readySockets = this->m_currentSocket;
        // std::cout << "dsadsa" << std::endl;
        for (int i = 0; i < m_clientSocket.size(); i++)
        {
            std::cout << "said: " << std::endl;
            sd = m_clientSocket[i];
            if (sd > 0)
                FD_SET(sd, &m_currentSocket);
            if (sd > m_maxFd)
                m_maxFd = sd;
        }
        if (select(this->m_maxFd + 1, &m_currentSocket, NULL, NULL, NULL) < 0)
        {
            perror("select:");
            // throw std::string("mushkil f select");
        }
        this->acceptNewConnection();
    }
}

void WebServer::acceptNewConnection()
{
    int i;
    int newSocket;
    Parse parse;
    std::string host;
    std::string response;
    std::string m_body = "samir";
    // for (int l = 0; l < m_server.size(); l++)
    // {
    //     std::cout << "segfault: " << m_server[l] << std::endl;
    // }
    // std::cout << "maxFd: " << this->m_maxFd << std::endl;
    for (i = 0; i <= this->m_maxFd; i++)
    {
        int sd;
        // std::cout << "maxfd ==> " << m_server[1] << std::endl;
        if (i < m_server.size())
            if (FD_ISSET(this->m_server[i], &m_currentSocket))
            {
                if ((newSocket = accept(m_server[i], (struct sockaddr *)&this->m_address, (socklen_t *)&this->m_addrlen)) < 0)
                    throw std::string("Accept Failed");
                std::cout << "New connection, socket fd is : " << newSocket << std::endl;
                m_clientSocket.push_back(newSocket);
                FD_SET(newSocket, &m_currentSocket);
                std::cout << "Adding to list of sockets as " << newSocket << std::endl;
                if (newSocket > this->m_maxFd)
                    this->m_maxFd = newSocket;
            }
        for (int i = 0; i < m_clientSocket.size(); i++)
        {
            sd = m_clientSocket[i];
            if (FD_ISSET(sd, &m_currentSocket))
            {
                if (this->m_request.parsingRequest(sd, &m_currentSocket, m_clientSocket, i))
                {

                    // std::cout << this->m_request.getHost() << std::endl;
                    for (int k = 0; k < this->m_webServ.getwebserv().size(); k++)
                    {
                        // std::cout << this->m_webServ.getwebserv().size() << std::endl;
                        parse = this->m_webServ.getwebserv()[k];
                        for (int j = 0; j < parse.getlisten().size(); j++)
                        {
                            host = parse.gethost();
                            host += ":";
                            host += std::to_string(parse.getlisten()[j]);
                            std::cout << "listen ===> " << parse.getlisten()[j] << std::endl;
                            std::cout << "===> " << host << std::endl;
                            if (host == this->m_request.getHost())
                            {
                                std::cout << "salam sahbi" << std::endl;
                                m_parse = parse;
                                break;
                            }
                        }
                    }
                    // response = "HTTP/1.1\nContent-Type: text/html\nContent-Length: 6\n\n samir";
                    // write(sd, response.c_str(), response.length());
                    // this->me

                    this->manageRequest(sd);
                }
                fcntl(sd, F_SETFL, O_NONBLOCK);
            }
        }
    }
}

std::vector<int> WebServer::getServer(void) const
{
    return m_server;
}
int WebServer::getMaxSocket(void) const
{
    return (this->m_maxSocket);
}
WebServer::~WebServer(void)
{
}

void WebServer::debug(std::string str)
{
    std::cout << "********************************" << std::endl;
    std::cout << "##" << str << "##" << std::endl;
    std::cout << "********************************" << std::endl;
}