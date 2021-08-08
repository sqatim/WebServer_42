/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/08 16:35:51 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP
#include <map>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <string>

typedef std::unordered_multimap<std::string, std::string> FreqMap;

typedef struct s_location
{
    std::string index;
    std::string auto_index;
    std::string allow_methods;
    std::string _return;
    std::string fastcgi_pass;
    std::string upload_methods;
    std::string upload_store;
    std::string name;
} t_location;

class Parse
{
protected:
    std::string listen;
    std::string sever_name;
    std::string root;
    std::string *error_page;
    std::string client_max_body_size;
    std::string host;
    t_location *location;
    int count_location;
    int count_error_page;

public:
    std::string file;
    std::map<std::string, std::string> my_map;
    Parse();
    void setlisten(std::string val);
    std::string getlisten();
    void setserver_name(std::string val);
    std::string getserver_name();
    void setroot(std::string val);
    std::string getroot();
    void sethost(std::string val);
    std::string gethost();
    void setclient_max_body_size(std::string val);
    std::string getclient_max_body_size();
    void seterror_page(std::string *val);
    std::string *geterror_page();
    void setcount_error_page(int va);
    int getcount_error_page();
    void setcount_location(int va);
    int getcount_location();
    void setlocation(t_location *val);
    t_location *getlocation();
    ~Parse();
};

std::string get_value(std::string str);
std::string get_key(std::string str);
int CountWords(std::string str);
void get_attributs(Parse *serv, FreqMap wf);
void    add_locations(Parse *serv);

#endif