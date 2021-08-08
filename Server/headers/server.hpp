#ifndef SERVER_HPP
#define SERVER_HPP

#include <fstream>
#include <iostream>
#include "get_next_line.hpp"

typedef struct s_header
{
    std::string version;
    std::string status;
    int contentLength;
    std::string contentType;
}               t_header;

typedef struct s_response
{
    t_header header;
    std::string body;
}               t_response;

t_header affectationHeader(std::string status, std::string type1, std::string type2, int length);
std::string responseConcatenation(t_header header, std::string body);
#endif