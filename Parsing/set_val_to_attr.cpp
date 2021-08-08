/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/08 16:35:38 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void    add_locations(Parse *serv)
{
    std::fstream file;
    std::string filename;
    std::string word;

    file.open(serv->file.c_str());
    // se serv->getcount_location() ;
    t_location * loc = new t_location[serv->getcount_location()];
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
                    continue ;
                if (word == "}")
                    break ;
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
    serv->setlocation(loc);
    i = 0;
    while (i < serv->getcount_location())
    {
        std::cout << serv->getlocation()[i].name << std::endl;
        if (serv->getlocation()[i].auto_index.length() > 0)
        {
            std::cout << serv->getlocation()[i].auto_index << std::endl;
        }
        if (serv->getlocation()[i].index.length() > 0)
        {
            std::cout << serv->getlocation()[i].index << std::endl;
        }
        if (serv->getlocation()[i].allow_methods.length() > 0)
        {
            std::cout << serv->getlocation()[i].allow_methods << std::endl;
        }
        if (serv->getlocation()[i]._return.length() > 0)
        {
            std::cout << serv->getlocation()[i]._return << std::endl;
        }
        if (serv->getlocation()[i].fastcgi_pass.length() > 0)
        {
            std::cout << serv->getlocation()[i].fastcgi_pass << std::endl;
        }
        if (serv->getlocation()[i].upload_methods.length() > 0)
        {
            std::cout << serv->getlocation()[i].upload_methods << std::endl;
        }
        if (serv->getlocation()[i].upload_store.length() > 0)
        {
            std::cout << serv->getlocation()[i].upload_store << std::endl;
        }
        std::cout << "=============================================" << std::endl;
        i++;
    }
}



void get_attributs(Parse *serv, FreqMap wf)
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
            serv->setlisten(aa);
        }
        if (nn == "root")
        {
            std::string aa = get_key(it->second);
            serv->setroot(aa);
        }
        if (nn == "server_name")
        {
            std::string aa = get_key(it->second);
            serv->setserver_name(aa);
        }
        if (nn == "host")
        {
            std::string aa = get_key(it->second);
            serv->sethost(aa);
        }
        if (nn == "client_max_body_size")
        {
            std::string aa = get_key(it->second);
            serv->setclient_max_body_size(aa);
        }
        if (nn == "error_page")
            count_error_page++;
        if (nn == "location")
            count_location++;
    }
    serv->setcount_error_page(count_error_page);
    serv->setcount_location(count_location);
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
    serv->seterror_page(err);
}
