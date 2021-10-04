#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>
#include "server.hpp"
#include <unistd.h>
#include <map>

typedef struct s_bodyPost
{
    std::string filename;
    std::string m_body;
} t_bodyPost;

typedef struct s_keyValue
{
    std::string key;
    std::string value;
} t_keyValue;

typedef struct s_chunked
{
    size_t length;
    size_t pos;
    int i;
    std::string m_body;
} t_chunked;

class Request
{
private:
    std::string m_method;
    std::string m_path;
    std::string m_version;
    std::string m_firstRequestheader;
    std::string m_host;
    std::string m_hostSolo;
    std::string m_portSolo;
    std::string m_userAgent;
    std::string m_accept;
    std::string m_cookie;
    std::string m_fastCgi;
    std::string m_contentType;
    std::string m_transferEncoding;
    std::string m_contentLength;
    std::string m_fileName;
    std::string m_betweenBoundary;
    std::string m_boundary;
    std::string m_query;
    size_t m_countContentLength;
    int m_check;
    std::vector<t_bodyPost> m_bodyPost;
    std::vector<t_keyValue> m_keyValue;
    std::vector<t_chunked> m_chunked;
    std::string m_body;
    std::string m_request;
    std::string m_mainRequest;
    std::map<int, std::string> m_requestMap;

public:
    Request();
    int concatRequest(int socket, fd_set *readySockets, fd_set *writeSockets, std::vector<int> &clientSocket, int i);
    int readingRequest(int socket, int &result);
    int parseRequest(int socket);
    void getWords();
    int requestHeaders(int socket, int& check);
    void concatenation();
    void parsingRequestLine(std::string line);
    int parsingRequestGet(int socket);
    int parsingRequestPost(char *buffer);
    void chunkedEncodingPost(std::string &line, int &length);
    void chunkedContentTypeApplication(std::string &line, int &length);
    void chunkedContentTypeMultipart(std::string &line, int &length);
    void chunkedContentTypeMultipartFirstBoundary(std::string &line, int &length);
    void contentLengthPost(std::string &line, size_t i);
    int checkIfFinishedOrNot(std::string &line, size_t &i);
    void parsingBetweenBoundary(int& check);
    void parseHost(std::string host);
    void uploadInFile(const char *path);
    void insetMapRequest(int socket);
    void init();
    int checkTheEndOfRequest(char *buffer);
    int checkTheEndOfRequestGetAndDelete(char *buffer);
    int checkTheEndOfRequestPost(char *buffer, int &length);
    void parsingKeyValue(std::string body);

    //  Accessors
    std::string getquery() const;
    std::string getMethod() const;
    std::string getPath() const;
    std::string getVersion() const;
    std::string getFirstRequestHeader() const;
    std::string getHost() const;
    std::string getUserAgent() const;
    std::string getAccept() const;
    std::string getAcceptEncoding() const;
    std::string getAcceptLanguage() const;
    std::string getConnection() const;
    std::string getCookie() const;
    std::string getContentLength() const;
    std::string getHostSolo() const;
    std::string getPortSolo() const;
    std::string getFastCgi() const;
    std::string getBody() const;
    std::string getRequest() const;
    std::string getBoundary() const;
    std::string getFileName() const;
    std::string getBetweenBoundary() const;
    std::vector<t_keyValue> getm_keyvalue() const;
    void setFastCgi(std::string fastCgi);
    void setRequest(std::string request);
    void setBody(std::string body);

    ~Request();
};

std::ostream &operator<<(std::ostream &out, Request &src);

#endif