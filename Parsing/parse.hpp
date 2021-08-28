/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/25 16:27:29 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP
#include <map>
// #include <bits/stdc++.h>
#include <unordered_map>
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

typedef struct s_listen
{
    std::string adress_ip;
    std::string port;
} t_listen;

class Parse
{
protected:
    std::vector<t_listen> listen;
    std::string server_name;
    std::string root;
    std::vector<std::string> error_page;
    std::string client_max_body_size;
    std::string host;
    std::vector<t_location> location;
    int count_location;
    int count_listen;
    int count_error_page;

public:
    void get_attributs(FreqMap wf);
    void add_locations();
    std::string file;
    std::map<std::string, std::string> my_map;
    Parse(std::string _filename);
    void setlisten( std::vector<t_listen> val);
    std::vector<t_listen> getlisten();
    void setserver_name(std::string val);
    std::string getserver_name();
    void setroot(std::string val);
    std::string getroot();
    void sethost(std::string val);
    std::string gethost();
    void setclient_max_body_size(std::string val);
    std::string getclient_max_body_size();
    void seterror_page(std::vector<std::string> val);
    std::vector<std::string> geterror_page();
    void setcount_error_page(int va);
    int getcount_error_page();
    void setcount_location(int va);
    int getcount_location();
    void setlocation(std::vector<t_location> val);
    std::vector<t_location> getlocation();
    ~Parse();
};

int check_keys(FreqMap wf);
std::string get_value(std::string str);
std::string get_key(std::string str);
int CountWords(std::string str);
int check_accolades(FreqMap wf, std::string filename);
void error(std::string str);
#endif

