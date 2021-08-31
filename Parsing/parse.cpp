/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:30 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/31 16:21:21 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

Parse::Parse(std::string _filename) : listen(0), server_name(0), root(""), error_page(0), client_max_body_size(""), host("")
{
    // FreqMap wf;
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
    int i = 0;
    // while (i < file_in_vector.size())
    // {
    //     std::cout << file_in_vector[i] << std::endl;
    //     i++;
    // }
    // int check = check_accolades(wf,_filename);
    // if (check != 0)
    //     error("Error in number of accolades");
    // check = check_keys(wf);
    // // std::cout << check << std::endl;
    // if (check == 0)
    //     error("Error in keys");
    get_attributs(file_in_vector);
    // add_locations();
}

Parse::Parse(Parse const &src)
{
    *this = src;
    return;
}

Parse &Parse::operator=(Parse const &src)
{
    if (this != &src)
    {
        this->listen = src.listen;
        this->server_name = src.server_name;
        this->root = src.root;
        this->error_page = src.error_page;
        this->client_max_body_size = src.client_max_body_size;
        this->host = src.host;
        this->location = src.location;
        this->count_location = src.count_location;
        this->count_listen = src.count_listen;
        this->count_error_page = src.count_error_page;
    }
    return *this;
}

Parse::~Parse()
{
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

void Parse::seterror_page(std::vector<std::string> val)
{
    this->error_page = val;
}
std::vector<std::string> Parse::geterror_page()
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
    if (in.geterror_page().size() > 0)
    {
        int i = 0;
        while (i < in.geterror_page().size())
        {
            out << "error_page " << i + 1 << " " << in.geterror_page()[i] << std::endl;
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
        // out << "amine" << std::endl;
        if (in.getlocation()[i].getindex().size() > 0)
            out << "index in location number " << i + 1 << " is: " << in.getlocation()[i].getindex() << std::endl;
        if (in.getlocation()[i].getauto_index().size() > 0)
            out << "auto_index in location number " << i + 1 << " is: " << in.getlocation()[i].getauto_index() << std::endl;
        if (in.getlocation()[i].getallow_methods().size() > 0)
            out << "allow_methods in location number " << i + 1 << " is: " << in.getlocation()[i].getallow_methods() << std::endl;
        if (in.getlocation()[i].get_return().length() != 0)
            out << "_return in location number " << i + 1 << " is: " << in.getlocation()[i].get_return() << std::endl;
        if (in.getlocation()[i].getfascgi_pass().size() > 0)
            out << "fastcgi_pass in location number " << i + 1 << " is: " << in.getlocation()[i].getfascgi_pass() << std::endl;
        if (in.getlocation()[i].getupload_methods().size() > 0)
            out << "upload_methods in location number " << i + 1 << " is: " << in.getlocation()[i].getupload_methods() << std::endl;
        if (in.getlocation()[i].getupload_store().size() > 0)
            out << "upload_store in location number " << i + 1 << " is: " << in.getlocation()[i].getupload_store() << std::endl;
        if (in.getlocation()[i].getname().size() > 0)
            out << "name in location number " << i + 1 << " is: " << in.getlocation()[i].getname() << std::endl;
        if (in.getlocation()[i].getroot().size() > 0)
            out << "root in location number " << i + 1 << " is: " << in.getlocation()[i].getroot() << std::endl;
        // out << "amine 2" << std::endl;std::endl
        i++;
    }
    return out;
}

void Parse::setIndex(std::string index)
{
    this->index = index;
}

std::string Parse::getIndex()
{
    return this->index;
}