#ifndef SERVER_HPP
#define SERVER_HPP

#include <fstream>
#include <iostream>

typedef struct s_content
{
    std::string root;
    std::string index;
    std::string locationReturn;
    std::string statusReturn;
    std::string optionalModifier;
}               t_content;

typedef struct s_header
{
    std::string version;
    std::string status;
    std::string contentLength;
    std::string contentType;
}               t_header;

typedef struct s_response
{
    t_header header;
    std::string body;
}               t_response;

t_header affectationHeader(std::string status, std::string type1, std::string type2, int length);
std::string responseConcatenation(t_header header, std::string body);
char **ft_split(std::string s, char c);
std::string getWord(char *str,  int nLine, int nWord);
// std::string notFountBody(std::string &body);
std::string defaultBody(std::string &body);
// std::string forbiddenBody(std::string &body);
// void manageRequest(std::string word, Parse parse);
#endif