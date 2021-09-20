/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:23:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/20 14:03:07 by amine            ###   ########.fr       */
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
    // this->file = filename;
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
    count_and_set_index(file_in_vector);
    // while (i < file_in_vector.size())
    // {
    //     std::cout << file_in_vector[i] << std::endl;
    //     i++;
    // }
    int check = 1;
    check = handle_error(file_in_vector);
    if (check == -1)
        std::cout << "wa ra keyn error" << std::endl;
        
    while (i < count_server)
    {
        // std::cout << "amine" << std::endl;
        Parse parse(_filename);
        get_attributs(file_in_vector, & parse, this->server_end_index[i], this->server_begin_index[i]);
        this->_webserv.push_back(parse);
        
        i++;
    }
    /* ha CGI asahbi */
    // CGI cg;
    // cg.execute("/home/amine/Desktop/WebServer_42/Parsing/index.php");
    // std::cout << cg.get_outpout() << std::endl;
    // i = 0;
    // while (i < this->_webserv.size())
    // {
    //     std::cout << "=========================== server number " << i+1 << "========" <<std::endl;
    //     std::cout << this->_webserv[i] << std::endl;
    //     i++;
    // }
    // std::cout << parse;
    // std::cout  << "amine" << std::endl;
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



int WebServ::handle_error(std::vector<std::string> file_in_vect)
{
    int check(1);
    int i = 0;
    if (this->server_begin_index.size() < 1 || this->server_end_index.size() < 1 ||
            this->server_end_index.size() != this->server_begin_index.size())
        return -1;
    while (i < file_in_vect.size())
    {
        if (check_line(file_in_vect[i]) == -1)
            return -1;
        i++;
    }
    return 0;
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
    // std::cout << count_server << std::endl;

    
}