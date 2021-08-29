/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/29 23:36:47 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"


FreqMap delete_semi_colomn(FreqMap wf)
{
    std::unordered_multimap<std::string, std::string>::iterator it;

    for (it = wf.begin(); it != wf.end(); ++it)
    {
        int find_semi_colomn;
        find_semi_colomn = get_key(it->second).find(";");
        if (find_semi_colomn > 0)
            it->second = get_key(it->second).substr(0,find_semi_colomn);
    }
    return wf;
}

std::string del_sem_col_in_str(std::string str)
{
    int find_semi_colomn;
    std::string ret;
    find_semi_colomn = str.find(";");
    if (find_semi_colomn > 0)
    {
        ret = str.substr(0,find_semi_colomn);
        return ret;
    }
    return str;
}

void Parse::add_locations()
{
    std::fstream file;
    // std::string filename;
    std::string str;
    
    file.open(this->file);
    int i = 0;
    // std::cout << this->file << std::endl;
    i = 0;
    while (getline(file, str, '\n'))
    {
        // i++;
        // std::cout << i << std::endl;
        LocaTion loc;
        int find  = str.find("location");
        if (find > 0)
        {
            loc.setname(get_value(str));
            while (getline(file, str, '\n'))
            {
                if (str == "}")
                    break;
                if (get_key(str) == "index")
                    loc.setindex(get_value(str));
            }
        }
        if (find > 0 )
        {
            this->location.push_back(loc);
            loc.~LocaTion();
            find = -1;
        }
        std::cout << str << std::endl;
    }
    // i = 0;
    // std::cout << this->location.size() << std::endl;
    // while (i < this->location.size())
    // {
    //     if (this->location[i].getname().size() > 0)
    //         std::cout << this->location[i].getname() << std::endl;
    //     if (this->location[i].getindex().size() > 0)
    //         std::cout << this->location[i].getindex() << std::endl;
    //     i++;
    // }
}



void Parse::get_attributs(FreqMap wf)
{
    int count_error_page = 0;
    int count_location = 0;
    // t_listen lis;
    count_listen = 0;
    std::unordered_multimap<std::string, std::string>::iterator it;
    wf = delete_semi_colomn(wf);
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        std::string nn = get_key(it->first);
        if (nn == "listen")
        {
            std::string aa = get_key(it->second);
            listen.push_back(std::stoi(aa));
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
    // int l = 0;
    // while (l < listen.size())
    // {
    //     std::cout << "port: " << listen[l].port << std::endl;
    //     std::cout << "address ip: " << listen[l].adress_ip << std::endl;
    //     l++;
    // }
    // /* here is the vector of listen but not in ordre*/
    // l = 0;
    // while (l < error_page.size())
    // {
    //     std::cout << error_page[l] << std::endl;
    //     l++;
    // }
}
