/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/08 14:58:42 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

server::server(/* args */)
{
    this->listen = "";
    this->sever_name = "";
    this->root = "";
    this->error_page= NULL;
    this->client_max_body_size= "";
    this->host= "";
    location = NULL;
}

server::~server()
{
}

void server::setlisten(std::string val)
{
    this->listen = val;
}

std::string server::getlisten()
{
    return this->listen;
}

void server::setserver_name(std::string val)
{
    this->sever_name = val;
}
std::string server::getserver_name()
{
    return this->sever_name;
}
void server::setroot(std::string val)
{
    this->root = val;
}
std::string server::getroot()
{
    return this->root;
}

void server::sethost(std::string val)
{
    this->host = val;
}

std::string server::gethost()
{
    return this->host;
}

void server::setclient_max_body_size(std::string val)
{
    this->client_max_body_size = val;
}

std::string server::getclient_max_body_size()
{
    return this->client_max_body_size;
}

void server::seterror_page(std::string * val)
{
    this->error_page = val;
}
std::string * server::geterror_page()
{
    return this->error_page;
}

void server::setcount_error_page(int va)
{
    this->count_error_page = va;
}
int  server::getcount_error_page()
{
    return this->count_error_page;
}

void server::setcount_location(int va)
{
    this->count_location = va;
}
int  server::getcount_location()
{
    return this->count_location;
} 

void server::setlocation(t_location *val)
{
    this->location = val;
}
t_location *server::getlocation()
{
    return this->location;
}