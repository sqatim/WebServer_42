/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/29 18:33:02 by ahaddad          ###   ########.fr       */
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
#include "location.hpp"
typedef std::unordered_multimap<std::string, std::string> FreqMap;

// typedef struct s_ret
// {
//     int redirec;
//     char *path;
// } t_ret;

// // typedef struct s_location
// // {
// // } t_location;

// class location
// {
// private:
//     std::string index;
//     std::string auto_index;
//     std::string allow_methods;
//     std::string _return;
//     std::string fastcgi_pass;
//     std::string upload_methods;
//     std::string upload_store;
//     std::string name;
//     std::string root;
//     /* data */
// public:
//     location(/* args */);
//     location(const location & src);
//     location &operator=(const location &f);
//     void setindex(std::string val);
//     std::string getindex();
//     void setauto_index(std::string val);
//     std::string getauto_index();
//     void setallow_methods(std::string val);
//     std::string getallow_methods();
//     void set_return(std::string val);
//     std::string get_return();
//     void setfascgi_pass(std::string val);
//     std::string getfascgi_pass();
//     void setupload_methods(std::string val);
//     std::string getupload_methods();
//     void setupload_store(std::string val);
//     std::string getupload_store();
//     void setname(std::string val);
//     std::string getname();
//     void setroot(std::string val);
//     std::string getroot();
//     ~location();
// };

// location loc;

class Parse
{
protected:
    std::vector<int> listen;
    std::string server_name;
    std::string root;
    std::vector<std::string> error_page;
    std::string client_max_body_size;
    std::string host;
    std::vector<LocaTion> location;
    int count_location;
    int count_listen;
    int count_error_page;

public:
    void get_attributs(FreqMap wf);
    void add_locations();
    std::string file;
    std::map<std::string, std::string> my_map;
    Parse(std::string _filename);
    void setlisten(std::vector<int> val);
    std::vector<int> getlisten();
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
    void setlocation(std::vector<LocaTion> val);
    std::vector<LocaTion>  getlocation();
    ~Parse();
};

int check_keys(FreqMap wf);
std::string get_value(std::string str);
std::string get_key(std::string str);
int CountWords(std::string str);
int check_accolades(FreqMap wf, std::string filename);
void error(std::string str);
#endif
