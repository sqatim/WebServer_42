#include "WebServer.class.hpp"

WebServer::WebServer(WebServ &webServ) : m_maxSocket(0), m_addrlen(sizeof(m_address)), m_webServ(webServ)
{
}

Server WebServer::setServer(Parse &parse)
{
    Server server(parse, m_maxSocket, m_server, m_address);
    return server;
}

void WebServer::run()
{
    size_t i;
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
        for (size_t i = 0; i < m_clientSocket.size(); i++)
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

int WebServer::theRightServerName(std::string &requestHost, Parse &parse, std::string &host, size_t &j)
{
    for (size_t counter = 0; counter < parse.getserver_name().size(); counter++)
    {
        requestHost = justValue(this->m_request.getHost());
        host = parse.getserver_name()[counter];
        host += ":";
        host += std::to_string(parse.getlisten()[j]);
        if (requestHost == host)
        {
            m_parse = parse;
            return (1);
        }
    }
    return (0);
}
void WebServer::choosingTheRightServer(std::string &requestHost, int &check)
{
    Parse parse;
    std::string host;
    for (size_t k = 0; k < this->m_webServ.getwebserv().size(); k++)
    {
        parse = this->m_webServ.getwebserv()[k];
        for (size_t j = 0; j < parse.getlisten().size(); j++)
        {
            host = parse.gethost();
            host += ":";
            host += std::to_string(parse.getlisten()[j]);
            if (host == requestHost || requestHost.compare(0, 10, "localhost:") == 0 || host.compare(0, 7, "0.0.0.0") == 0)
            {
                m_parse = parse;
                check = 1;
                break;
            }
            if (check == 0)
                check = theRightServerName(requestHost, parse, host, j);
        }
    }
}

void WebServer::checkingClient()
{
    int request;
    std::string requestHost;
    int check = 0;
    int socket;

    for (size_t i = 0; i < m_clientSocket.size(); i++)
    {
        socket = m_clientSocket[i];
        request = 0;
        if (FD_ISSET(socket, &m_currentSocket))
        {
            check = 0;
            if ((request = this->m_request.concatRequest(socket, &m_currentSocket, &m_writeSocket, m_clientSocket, i)) < 0)
            {
                this->m_request.requestHeaders(socket, request);
                requestHost = justValue(this->m_request.getHost());
                choosingTheRightServer(requestHost, check);
                if (FD_ISSET(socket, &m_writeSocket))
                {
                    this->manageRequest(socket, check, request);
                    this->m_request.init();
                    this->m_response.initResponse();
                }
            }
        }
    }
}

void WebServer::acceptNewConnection()
{
    int i;
    int newSocket;
    for (i = 0; i <= this->m_maxFd; i++)
    {
        if (i < (int)m_server.size())
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
    }
    checkingClient();
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