/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/01 15:32:38 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

Parse::Parse(std::string _filename) : listen(0), server_name(0), root(""), error_page(0), client_max_body_size(""), host("")
{
    std::string word;
    std::fstream file;
    std::string filename;
    std::string name;
    filename = _filename;
    this->file = filename;
    file.open(filename);
    std::vector<std::string> file_in_vector;
    while (getline(file, word))
    {
        if (is_printable(word) == 1)
            file_in_vector.push_back(word);
    }
    get_attributs(file_in_vector);
}

Parse::~Parse()
{
}

Parse::Parse(const Parse &src)
{
    this->listen = src.listen;
    this->server_name = src.server_name;
    this->index = src.index;
    this->root = src.root;
    this->host = src.host;
    this->error_page = src.error_page;
    this->client_max_body_size = src.client_max_body_size;
    this->location = src.location;
}
Parse &Parse::operator=(const Parse &src)
{
    this->listen = src.listen;
    this->server_name = src.server_name;
    this->index = src.index;
    this->root = src.root;
    this->host = src.host;
    this->error_page = src.error_page;
    this->client_max_body_size = src.client_max_body_size;
    this->location = src.location;
    return *this;
}

void Parse::setlisten(std::vector<int> val)
{
    this->listen = val;
}

std::vector<int> Parse::getlisten()
{
    return this->listen;
}

void Parse::setserver_name(std::vector<std::string> val)
{
    this->server_name = val;
}
std::vector<std::string> Parse::getserver_name()
{
    return this->server_name;
}
void Parse::set_Index(std::vector<std::string> val)
{
    this->index = val;
}
std::vector<std::string> Parse::get_Index()
{
    return this->index;
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
void Parse::setIndexToUse(std::string val)
{
    this->indexToUse = val;
}

std::string Parse::getIndexToUse()
{
    return this->indexToUse;
}

void Parse::setclient_max_body_size(std::string val)
{
    this->client_max_body_size = val;
}

std::string Parse::getclient_max_body_size()
{
    return this->client_max_body_size;
}

void Parse::seterror_page(std::vector<t_ret> val)
{
    this->error_page = val;
}

std::vector<t_ret> Parse::geterror_page()
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

void Parse::setlocation(std::vector<LocaTion> val)
{
    this->location = val;
}
std::vector<LocaTion> Parse::getlocation()
{
    return this->location;
}

std::ostream &operator<<(std::ostream &out, Parse &in)
{
    if (in.getlisten().size() > 0)
    {
        int i = 0;
        while (i < in.getlisten().size())
        {
            out << "listen " << i + 1 << " " << in.getlisten()[i] << std::endl;
            i++;
        }
    }
    if (in.getserver_name().size() > 0)
    {
        int i = 0;
        while (i < in.getserver_name().size())
        {
            out << "server_name " << i + 1 << " " << in.getserver_name()[i] << std::endl;
            i++;
        }
    }
    if (in.get_Index().size() > 0)
    {
        int i = 0;
        while (i < in.get_Index().size())
        {
            out << "index " << i + 1 << " {" << in.get_Index()[i] << "}" << std::endl;
            i++;
        }
    }
    if (in.geterror_page().size() > 0)
    {
        int i = 0;
        while (i < in.geterror_page().size())
        {
            out << "error_page " << i + 1 << " redirect: " << in.geterror_page()[i].redirec << std::endl;
            out << "path :" << in.geterror_page()[i].path << std::endl;
            i++;
        }
    }
    if (in.getroot().size() > 0)
    {
        out << "root " << in.getroot() << std::endl;
    }
    if (in.getclient_max_body_size().size() > 0)
    {
        out << "client_max_body_size " << in.getclient_max_body_size() << std::endl;
    }
    if (in.gethost().size() > 0)
    {
        out << "host " << in.gethost() << std::endl;
    }
    int i = 0;
    while (i < in.getlocation().size())
    {
        if (in.getlocation()[i].getindex().size() > 0)
        {
            int k = 0;
            while (k < in.getlocation()[i].getindex().size())
            {
                out << "index in location number " << i + 1 << " is: {" << in.getlocation()[i].getindex()[k] << "}" << std::endl;
                k++;
            }
        }
        if (in.getlocation()[i].getauto_index().size() > 0)
            out << "auto_index in location number " << i + 1 << " is: {" << in.getlocation()[i].getauto_index() << "}" << std::endl;
        if (in.getlocation()[i].getallow_methods().size() > 0)
            out << "allow_methods in location number " << i + 1 << " is: {" << in.getlocation()[i].getallow_methods() << "}" << std::endl;
        if (in.getlocation()[i].get_return().size() != 0)
        {
            int k = 0;
            while (k < in.getlocation()[i].get_return().size())
            {
                out << "_return in location number " << i + 1 << "int  is: {" << in.getlocation()[i].get_return()[k].redirec << "}" << std::endl;
                out << "_return in location number " << i + 1 << "path  is: {" << in.getlocation()[i].get_return()[k].path << "}" << std::endl;
                k++;
            }
        }
        if (in.getlocation()[i].getfascgi_pass().size() > 0)
            out << "fastcgi_pass in location number " << i + 1 << " is: {" << in.getlocation()[i].getfascgi_pass() << "}" << std::endl;
        if (in.getlocation()[i].getupload_methods().size() > 0)
            out << "upload_methods in location number " << i + 1 << " is: {" << in.getlocation()[i].getupload_methods() << "}" << std::endl;
        if (in.getlocation()[i].getupload_store().size() > 0)
            out << "upload_store in location number " << i + 1 << " is: {" << in.getlocation()[i].getupload_store() << "}" << std::endl;
        if (in.getlocation()[i].getname().size() > 0)
            out << "name in location number " << i + 1 << " is: {" << in.getlocation()[i].getname() << "}" << std::endl;
        if (in.getlocation()[i].getroot().size() > 0)
            out << "root in location number " << i + 1 << " is: {" << in.getlocation()[i].getroot() << "}" << std::endl;
        i++;
    }
    return out;
}
