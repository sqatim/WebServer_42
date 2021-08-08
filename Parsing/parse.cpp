/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/08 19:03:06 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

Parse::Parse(std::string _filename) : listen(""), server_name(""), root(""), error_page(NULL), client_max_body_size(""), host(""), location(NULL)
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
    get_attributs(wf);
    std::cout << this->listen << std::endl;
    std::cout << this->host << std::endl;
    std::cout << this->root << std::endl;
    std::cout << this->server_name << std::endl;
    std::cout << this->client_max_body_size << std::endl;
    int i = 0;
    while (i < this->count_error_page)
    {
        std::cout << this->error_page[i] << std::endl;
        i++;
    }
    std::cout << this->count_location << std::endl;
    add_locations(); 
}

Parse::~Parse()
{
}

void Parse::setlisten(std::string val)
{
    this->listen = val;
}

std::string Parse::getlisten()
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

void Parse::seterror_page(std::string *val)
{
    this->error_page = val;
}
std::string *Parse::geterror_page()
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

void Parse::setlocation(t_location *val)
{
    this->location = val;
}
t_location *Parse::getlocation()
{
    return this->location;
}