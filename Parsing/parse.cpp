/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/08 16:31:48 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

Parse::Parse(/* args */)
{
    this->listen = "";
    this->sever_name = "";
    this->root = "";
    this->error_page= NULL;
    this->client_max_body_size= "";
    this->host= "";
    location = NULL;
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
    this->sever_name = val;
}
std::string Parse::getserver_name()
{
    return this->sever_name;
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

void Parse::seterror_page(std::string * val)
{
    this->error_page = val;
}
std::string * Parse::geterror_page()
{
    return this->error_page;
}

void Parse::setcount_error_page(int va)
{
    this->count_error_page = va;
}
int  Parse::getcount_error_page()
{
    return this->count_error_page;
}

void Parse::setcount_location(int va)
{
    this->count_location = va;
}
int  Parse::getcount_location()
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