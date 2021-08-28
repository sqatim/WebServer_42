/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/27 13:59:40 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

Parse::Parse(std::string _filename) : listen(0), server_name(""), root(""), error_page(0), client_max_body_size(""), host(""), location(0)
{
    FreqMap wf;
    std::string word;
    std::fstream file;
    std::string filename;
    std::string name;
    filename = _filename;
    this->file = filename;
    file.open(filename.c_str());
    while (getline(file ,word))
    {
        int len = CountWords(word);
        if (len > 0)
        {
            wf.insert(std::pair<std::string , std::string>(get_key(word), get_value(word)));
        }
    }
    int check = check_accolades(wf,_filename);
    if (check != 0)
        error("Error in number of accolades");
    check = check_keys(wf);
    // std::cout << check << std::endl;
    if (check == 0)
        error("Error in keys"); 
    get_attributs(wf);
    add_locations(); 
}

Parse::~Parse()
{
}

void Parse::setlisten( std::vector<t_listen>val)
{
    this->listen = val;
}

std::vector<t_listen> Parse::getlisten()
{
    return this->listen;
}

void Parse::setserver_name(std::string val)
{
    this->server_name = val;
}
std::string Parse::getserver_name()
{
    return this->server_name;
}
void Parse::setroot(std::string val)
{
    this->root = val;
}
std::string Parse::getroot()
{
    return this->root;
}

void Parse::sethost(std::string val)
{
    this->host = val;
}

std::string Parse::gethost()
{
    return this->host;
}

void Parse::setclient_max_body_size(std::string val)
{
    this->client_max_body_size = val;
}

std::string Parse::getclient_max_body_size()
{
    return this->client_max_body_size;
}

void Parse::seterror_page(std::vector<std::string>val)
{
    this->error_page = val;
}
std::vector<std::string>Parse::geterror_page()
{
    return this->error_page;
}

void Parse::setcount_error_page(int va)
{
    this->count_error_page = va;
}

int Parse::getcount_error_page()
{
    return this->count_error_page;
}

void Parse::setcount_location(int va)
{
    this->count_location = va;
}
int Parse::getcount_location()
{
    return this->count_location;
}

void Parse::setlocation(std::vector<t_location> val)
{
    this->location = val;
}

std::vector<t_location> Parse::getlocation()
{
    return this->location;
}
