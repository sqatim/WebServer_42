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
    // struct timeval _tv = {1, 0};
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
    while (1)
    {
        FD_ZERO(&this->m_currentSocket);
        FD_ZERO(&this->m_writeSocket);
        for (i = 0; i < this->m_server.size(); i++)
        {
            FD_SET(this->m_server[i], &this->m_currentSocket);
            this->m_maxFd = this->m_server[i];
        }
        for (int i = 0; i < m_clientSocket.size(); i++)
        {
            sd = m_clientSocket[i];
            if (sd > 0)
            {
                FD_SET(sd, &m_currentSocket);
                FD_SET(sd, &m_writeSocket);
            }
            if (sd > m_maxFd)
                m_maxFd = sd;
        }
        if (select(this->m_maxFd + 1, &m_currentSocket, &m_writeSocket, NULL, NULL) < 0)
        {
            perror("select:");
            throw std::string("mushkil f select");
        }
        this->acceptNewConnection();
    }
}

void WebServer::acceptNewConnection()
{
    int i;
    int newSocket;
    Parse parse;
    std::string requestHost;
    std::string host;
    std::string response;
    std::string m_body = "samir";
    for (i = 0; i <= this->m_maxFd; i++)
    {
        int sd;
        if (i < m_server.size())
        {
            if (FD_ISSET(this->m_server[i], &m_currentSocket))
            {
                if ((newSocket = accept(m_server[i], (struct sockaddr *)&this->m_address, (socklen_t *)&this->m_addrlen)) < 0)
                    throw std::string("Accept Failed");
                fcntl(newSocket, F_SETFL, O_NONBLOCK);
                std::cout << "New connection, socket fd is : " << newSocket << std::endl;
                m_clientSocket.push_back(newSocket);
                FD_SET(newSocket, &m_currentSocket);
                FD_SET(newSocket, &m_writeSocket);
                std::cout << "Adding to list of sockets as " << newSocket << std::endl;
                if (newSocket > this->m_maxFd)
                    this->m_maxFd = newSocket;
            }
        }
        for (int i = 0; i < m_clientSocket.size(); i++)
        {
            sd = m_clientSocket[i];
            if (FD_ISSET(sd, &m_currentSocket))
            {
                if (this->m_request.parsingRequest(sd, &m_currentSocket, &m_writeSocket, m_clientSocket, i))
                {

                    for (int k = 0; k < this->m_webServ.getwebserv().size(); k++)
                    {
                        // std::cout << this->m_webServ.getwebserv().size() << std::endl;
                        parse = this->m_webServ.getwebserv()[k];
                        for (int j = 0; j < parse.getlisten().size(); j++)
                        {
                            host = parse.gethost();
                            host += ":";
                            host += std::to_string(parse.getlisten()[j]);
                            requestHost = justHost(this->m_request.getHost());
                            if (host == requestHost)
                            {
                                m_parse = parse;
                                break;
                            }
                        }
                    }
                    if (FD_ISSET(sd, &m_writeSocket))
                    {
                        if (m_request.getMethod() == "GET")
                        {
                            this->manageRequest(sd);
                            this->m_request.init();
                        }
                        else if (m_request.getMethod() == "POST")
                        {
                            response = "HTTP/1.1\nContent-Type: text/html\nContent-Length: 6\n\n samir";
                            write(sd, response.c_str(), response.length());
                            this->m_request.init();
                        }
                    }
                }
            }
            // {
            //     std::cout << "salam sahbi samir" << std::endl;
            // }
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