/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/22 13:18:11 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void Parse::add_locations()
{
    std::fstream file;
    std::string filename;
    std::string word;

    file.open(this->file.c_str());
    // se serv->getcount_location() ;
    t_location *loc = new t_location[this->count_location];
    int i = 0;
    while (file >> word)
    {
        if (word == "location")
        {
            file >> word;
            loc[i].name = word;
            while (file >> word)
            {
                if (word == "{")
                    continue;
                if (word == "}")
                    break;
                if (word == "autoindex")
                {
                    file >> word;
                    loc[i].auto_index = word;
                }
                if (word == "index")
                {
                    file >> word;
                    loc[i].index = word;
                }
                if (word == "allow_methods")
                {
                    file >> word;
                    loc[i].allow_methods = word;
                }
                if (word == "return")
                {
                    file >> word;
                    loc[i]._return = word;
                }
                if (word == "fastcgi_pass")
                {
                    file >> word;
                    loc[i].fastcgi_pass = word;
                }
                if (word == "upload_methods")
                {
                    file >> word;
                    loc[i].upload_methods = word;
                }
                if (word == "upload_store")
                {
                    file >> word;
                    loc[i].upload_store = word;
                }
            }
            i++;
        }
    }
    this->location = loc;
    i = 0;
    // while (i < this->count_location)
    // {
    //     std::cout << this->location[i].name << std::endl;
    //     if (this->location[i].auto_index.length() > 0)
    //     {
    //         std::cout << this->location[i].auto_index << std::endl;
    //     }
    //     if (this->location[i].index.length() > 0)
    //     {
    //         std::cout << this->location[i].index << std::endl;
    //     }
    //     if (this->location[i].allow_methods.length() > 0)
    //     {
    //         std::cout << this->location[i].allow_methods << std::endl;
    //     }
    //     if (this->location[i]._return.length() > 0)
    //     {
    //         std::cout << this->location[i]._return << std::endl;
    //     }
    //     if (this->location[i].fastcgi_pass.length() > 0)
    //     {
    //         std::cout << this->location[i].fastcgi_pass << std::endl;
    //     }
    //     if (this->location[i].upload_methods.length() > 0)
    //     {
    //         std::cout << this->location[i].upload_methods << std::endl;
    //     }
    //     if (this->location[i].upload_store.length() > 0)
    //     {
    //         std::cout << this->location[i].upload_store << std::endl;
    //     }
    //     std::cout << "=============================================" << std::endl;
    //     i++;
    // }
}

void Parse::get_attributs(FreqMap wf)
{
    int count_error_page = 0;
    int count_location = 0;
    std::unordered_multimap<std::string, std::string>::iterator it;
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        std::string nn = get_key(it->first);
        std::cout << "{" << nn << "}\n";
        if (nn == "listen")
        {
            std::string aa = get_key(it->second);
            this->listen = aa;
        }
        if (nn == "root")
        {
            std::string aa = get_key(it->second);
            this->root = aa;
        }
        if (nn == "server_name")
        {
            std::string aa = get_key(it->second);
            this->server_name = aa;
        }
        if (nn == "host")
        {
            std::string aa = get_key(it->second);
            this->host = aa;
        }
        if (nn == "client_max_body_size")
        {
            std::string aa = get_key(it->second);
            this->client_max_body_size = aa;
        }
        if (nn == "error_page")
            count_error_page++;
        if (nn == "location")
            count_location++;
    }
    this->count_error_page = count_error_page;
    this->count_location = count_location;
    std::string *err = new std::string[count_error_page];
    int k = 0;
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        std::string nn = get_key(it->first);
        if (nn == "error_page")
        {
            std::string aa = it->second;
            err[k] = aa;
            k++;
        }
    }
    this->error_page = err;
}
