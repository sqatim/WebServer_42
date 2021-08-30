/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/30 13:47:28 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP
#include <map>
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

class Parse
{
protected:
    std::vector<int> listen;
    std::vector<std::string> server_name;
    std::string root;
    std::vector<std::string> error_page;
    std::string client_max_body_size;
    std::string host;
    std::vector<LocaTion> location;
    int count_location;
    int count_listen;
    int count_error_page;

public:
    void get_attributs(std::vector<std::string> vect);
    std::string file;
    std::map<std::string, std::string> my_map;
    Parse(std::string _filename);
    void setlisten(std::vector<int> val);
    std::vector<int> getlisten() ;
    void setserver_name(std::vector<std::string> val);
    std::vector<std::string> getserver_name();
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

std::ostream &operator<<(std::ostream &out, Parse &pars);

void add_locations();
int check_keys(FreqMap wf);
std::string get_value(std::string str);
std::string get_key(std::string str);
int CountWords(std::string str);
int check_accolades(FreqMap wf, std::string filename);
void error(std::string str);
int is_printable(std::string str);
#endif
