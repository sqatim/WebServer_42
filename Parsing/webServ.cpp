/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:23:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/17 21:38:28 by amine            ###   ########.fr       */
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
    count_and_set_index(file_in_vector);
    int i = 0;
    // std::cout << count_server << std::endl;
    while (i < count_server)
    {
        // std::cout << "amine" << std::endl;
        Parse parse(_filename);
        get_attributs(file_in_vector, & parse, this->server_end_index[i], this->server_begin_index[i]);
        this->_webserv.push_back(parse);
        
        i++;
    }
    /* ha CGI asahbi */
    CGI cg;
    cg.execute("/home/amine/Desktop/WebServer_42/Parsing/index.php");
    std::cout << cg.get_outpout() << std::endl;
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