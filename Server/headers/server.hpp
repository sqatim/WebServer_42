#ifndef SERVER_HPP
#define SERVER_HPP

#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include "../../Parsing/parse.hpp"
#include "Request.class.hpp"

class Request;

char **ft_split(std::string s, char c);
std::string getWord(char *str, int nLine, int nWord);
std::string defaultBody(std::string &body);
std::string getRoot(LocaTion &location, Parse &parse, int which);
int getIndex(LocaTion &location, Parse &parse, int which, std::string &root);
std::string ft_joinSlash(char **array, const char *path);
int fileOrDir(const char *path);
void slash(std::string *path);
std::string getRoot(LocaTion &location, Parse &parse, int which);
int getIndex(LocaTion &location, Parse &parse, int which, std::string &root);
int ft_comparaison(std::string location, std::string uri);
int ft_cgi(std::string path);
int checkLocation(LocaTion location);
int appendUrlCgi(std::string &path, LocaTion location, std::string url);
std::string getUrl(Request &request);
std::string justValue(std::string host);
std::vector<LocaTion> locationSorted(std::vector<LocaTion> location);
void lastSlash(std::string &string);
size_t ft_strlen(const char *str);
char *ft_strdup(const char *s1);
int fastCgi(Request &request, Parse &parse, std::string &root, LocaTion &location);

#endif