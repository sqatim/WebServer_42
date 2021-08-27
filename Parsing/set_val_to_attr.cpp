/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/25 13:22:31 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void Parse::add_locations()
{
    std::fstream file;
    std::string filename;
    std::string word;

    file.open(this->file.c_str());
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
    t_listen lis;
    count_listen = 0;
    std::unordered_multimap<std::string, std::string>::iterator it;
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        int find_eol;
        find_eol = get_key(it->second).find(";");
        if (find_eol > 0)
            it->second = get_key(it->second).substr(0,find_eol);
    }
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        std::string nn = get_key(it->first);
        if (nn == "listen")
        {
            int search_ip = 0;
            int len  = get_key(it->second).size();
            lis.adress_ip = "0.0.0.0";
            lis.port = "80";
            search_ip = get_key(it->second).find(":");
            if (search_ip > 0)
            {
                lis.adress_ip = get_key(it->second).substr(0, search_ip);
                lis.port = get_key(it->second).substr(search_ip + 1, len);
            }
            else  if (search_ip < 0)
                lis.port = get_key(it->second);
            listen.push_back(lis);
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
        {
            this->error_page.push_back(it->second);
        }
        if (nn == "location")
            count_location++;
    }
    this->count_location = count_location;
    /* here is the vector of listen but not in ordre*/
    int l = 0;
    while (l < listen.size())
    {
        std::cout << "port: " << listen[l].port << std::endl;
        std::cout << "adress ip: " << listen[l].adress_ip << std::endl;
        l++;
    }
    // /* here is the vector of listen but not in ordre*/
    // l = 0;
    // while (l < error_page.size())
    // {
    //     std::cout << error_page[l] << std::endl;
    //     l++;
    // }
}
