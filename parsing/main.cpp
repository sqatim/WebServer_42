/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/08 15:24:11 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void    add_locations(server *serv)
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


int main()
{
    FreqMap wf;
    std::string word;
    std::ifstream infile("webserv.conf");
    std::fstream file;
    std::string filename;
    std::string name;
    server serv;
    filename = "webserv.conf";
    serv.file = filename;
    file.open(filename.c_str());
    while (getline(file ,word))
    {
        int len = CountWords(word);
        if (len > 0)
        {
            wf.insert(std::pair<std::string , std::string>(get_key(word), get_value(word)));
        }
    }
    get_attributs(&serv, wf);
    std::cout << serv.getlisten() << std::endl;
    std::cout << serv.gethost() << std::endl;
    std::cout << serv.getroot() << std::endl;
    std::cout << serv.getserver_name() << std::endl;
    std::cout << serv.getclient_max_body_size() << std::endl;
    int i = 0;
    while (i < serv.getcount_error_page())
    {
        std::cout << serv.geterror_page()[i] << std::endl;
        i++;
    }
    std::cout << serv.getcount_location() << std::endl;
    add_locations(&serv);
    return 0;
}