/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:23:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/30 16:49:14 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "cgi.hpp"

WebServ::WebServ(std::string _filename)
{
    std::string word;
    std::fstream file;
    std::string filename;
    std::string name;
    count_server = 0;
    filename = _filename;
    file.open(filename);
    std::vector<std::string> file_in_vector;
    while (getline(file, word))
    {
        if (is_printable(word) == 1)
            file_in_vector.push_back(word);
    }
    int i = 0;
    while (i < file_in_vector.size())
    {
        std::vector<std::string> vect_str = splitstring(file_in_vector[i], " ");
        if (vect_str[0][0] == '#')
        {
            file_in_vector.erase(file_in_vector.begin()+i);
            i--;
        }
        i++;
    }
    i = 0;
    while (i < file_in_vector.size())
    {
        int j = 0;
        std::vector<std::string> vect_s = splitstring(file_in_vector[i], " ");
        std::string str;
        while (j < vect_s.size())
        {
            std::string str_get = get_key(vect_s[j]);
            str_get = get_key_tab(str_get);
            if (str_get.length() > 0)
            {
                str += str_get;
                str += " ";
            }
            j++;
        }
        file_in_vector[i] = str;
        i++;
    }
    count_and_set_index(file_in_vector);
    int check = 1;
    check = handle_error(file_in_vector);
    if (check == -1)
    {
        std::cout << "wa ra keyn error" << std::endl;
        exit(0);
    }
    i = 0;
    while (i < count_server)
    {
        Parse parse(_filename);
        if (get_attributs(file_in_vector, & parse, this->server_end_index[i], this->server_begin_index[i]) == -1)
        {
            std::cout << "wa ra keyn error f listen" << std::endl;
            return ;
        }
        this->_webserv.push_back(parse);        
        i++;
    }
}

WebServ::~WebServ()
{
}

int check_line(std::string str)
{
    int check = 1;
    std::vector<std::string> vect_str = splitstring(str, " ");
    int i = 0;
    if (vect_str.size() > 3)
        check = -1;
    if (vect_str.size() == 1)
    {
        if (vect_str[0] != "["  && vect_str[0] != "]" && vect_str[0] != "server" && vect_str[0] != "}" && vect_str[0] != "{")
            check  = -1;
    }
    if (vect_str.size() == 3)
    {
        if (vect_str[0] != "error_page" && vect_str[0] != "return")
            check = -1;
    }
    if (vect_str.size() == 2)
    {
        if (vect_str[0] != "listen" && vect_str[0] != "server_name" && vect_str[0] != "index" &&
            vect_str[0] != "root" && vect_str[0] != "location" && vect_str[0] != "client_max_body_size" &&
            vect_str[0] != "host" && vect_str[0] != "auto_index" && vect_str[0] != "fastcgi_pass" &&
            vect_str[0] != "allow_methods" && vect_str[0] != "upload_methods" &&vect_str[0] != "upload_store")
        check = -1;
    }
    return check;
}

int check_serv_loca(std::vector<std::string> vect)
{
    int check(1);
    int i = 0;
    while (i < vect.size())
    {
        std::vector<std::string> vect_str = splitstring(vect[i], " ");
        if (vect_str[0] == "server")
        {
            i++;
            if (i < vect.size())
            {
                std::vector<std::string> vect_str = splitstring(vect[i], " ");
                if (vect_str.size() > 1 || vect_str[0] != "[")
                    return -1;
            }
        }
        if (vect_str[0] == "location")
        {
            i++;
            if (i < vect.size())
            {
                std::vector<std::string> vect_str = splitstring(vect[i], " ");
                if (vect_str.size() > 1 || vect_str[0] != "{")
                    return -1;
            }
        }
        i++;
    }
    return check;
}

int WebServ::handle_error(std::vector<std::string> file_in_vect)
{
    int check(1);
    int i = 0;
    if (this->server_begin_index.size() < 1 || this->server_end_index.size() < 1 ||
            this->server_end_index.size() != this->server_begin_index.size())
    {
        return -1;
    }
    while (i < file_in_vect.size())
    {
        if (check_line(file_in_vect[i]) == -1)
            return -1;
        i++;
    }
    if (check_serv_loca(file_in_vect) == -1)
        return -1;
    return check;
}

void WebServ::setwebserv(std::vector<Parse> val)
{
    this->_webserv = val;
}

std::vector<Parse> WebServ::getwebserv()
{
    return this->_webserv;
}

void WebServ::count_and_set_index(std::vector<std::string> vect)
{
    int i = 0;
    int count = 0;
    std::vector<int> tmp;
    i = 0;
    while (i <vect.size())
    {
        std::vector<std::string> vect_str = splitstring(vect[i], " ");
        if (vect_str.size() == 1)
        {
            if (vect_str[0] == "server")
            {
                this->count_server++;                          
            }
            if (vect_str[0] == "]")
            {
                this->server_end_index.push_back(i);                          
            }
            if (vect_str[0] == "[")
            {
                this->server_begin_index.push_back(i);                          
            }
        }
        i++;
    }
}