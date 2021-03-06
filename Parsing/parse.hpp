/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/30 14:37:12 by amine            ###   ########.fr       */
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
    std::vector<std::string> index;
    std::string root;
    std::string indexToUse;
    std::vector<t_ret> error_page;
    std::string client_max_body_size;
    std::string host;
    std::vector<LocaTion> location;
    int count_location;
    int count_listen;
    int count_error_page;

public:
    std::string file;
    std::map<std::string, std::string> my_map;
    Parse();
    Parse(std::string _filename);
    Parse(const Parse &src);
    Parse &operator=(const Parse &src);
    void setlisten(std::vector<int> val);
    std::vector<int> getlisten();
    void setserver_name(std::vector<std::string> val);
    std::vector<std::string> getserver_name();
    void set_Index(std::vector<std::string> val);
    std::vector<std::string> get_Index();
    void setroot(std::string val);
    std::string getroot();
    void setIndexToUse(std::string val);
    std::string getIndexToUse();
    void sethost(std::string val);
    std::string gethost();
    void setclient_max_body_size(std::string val);
    std::string getclient_max_body_size();
    void seterror_page(std::vector<t_ret> val);
    std::vector<t_ret> geterror_page();
    void setcount_error_page(int va);
    int getcount_error_page();
    void setcount_location(int va);
    int getcount_location();
    void setlocation(std::vector<LocaTion> val);
    std::vector<LocaTion> getlocation();
    ~Parse();
};

int get_attributs(std::vector<std::string> vect, Parse *parse, int server_len, int _begin);
std::ostream &operator<<(std::ostream &out, Parse &pars);

void add_locations();
int check_keys(FreqMap wf);
std::string get_value(std::string str);
std::string get_key(std::string str);
int CountWords(std::string str);
int check_accolades(FreqMap wf, std::string filename);
void error(std::string str);
int is_printable(std::string str);
std::vector<std::string> splitstring(std::string str, std::string to_split_with);
std::vector<std::string> splitstring_with_point(std::string str, std::string to_split_with);
std::string get_key_tab(std::string str);
#endif
