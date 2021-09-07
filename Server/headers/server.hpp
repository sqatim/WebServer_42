#ifndef SERVER_HPP
#define SERVER_HPP

#include <fstream>
#include <iostream>
#include "get_next_line.hpp"

char **ft_split(std::string s, char c);
std::string getWord(char *str, int nLine, int nWord);
std::string defaultBody(std::string &body);
#endif