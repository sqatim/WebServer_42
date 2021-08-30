/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/30 16:16:08 by ahaddad          ###   ########.fr       */
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
            it->second = get_key(it->second).substr(0, find_semi_colomn);
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
        ret = str.substr(0, find_semi_colomn);
        return ret;
    }
    return str;
}

void add_locations()
{
}

void Parse::get_attributs(std::vector<std::string> vect)
{
    int i = 0;

    while (i < vect.size())
    {
        if (vect[i].find("listen") > 0)
        {
            if (get_key(vect[i]) == "listen")
                this->listen.push_back(std::stoi(get_value(vect[i])));
        }
        if (vect[i].find("server_name") > 0)
        {
            if (get_key(vect[i]) == "server_name")
                this->server_name.push_back(get_value(vect[i]));
        }
        if (vect[i].find("error_page") > 0)
        {
            if (get_key(vect[i]) == "error_page")
                this->error_page.push_back(get_value(vect[i]));
        }
        if (vect[i].find("root") > 0)
        {
            if (get_key(vect[i]) == "root")
                this->root = get_value(vect[i]);
        }
        if (vect[i].find("client_max_body_size") > 0)
        {
            if (get_key(vect[i]) == "client_max_body_size")
                this->client_max_body_size = get_value(vect[i]);
        }
        if (vect[i].find("host") > 0)
        {
            // space before ip
            std::string str;
            if (get_key(vect[i]) == "host")
            {
                str  =  get_value(vect[i]);
                this->host = get_key(str);
            }
        }
        std::string str = vect[i];
        if (vect[i].find("location") != -1)
        {
            LocaTion loc = LocaTion();
            loc.setname(get_value(vect[i]));
            // int ff = vect[i].find("location");
            // std::cout << vect[i] << "====>" << ff << std::endl;
            // int i = i++;
            while (i < vect.size())
            {
                if (vect[i].find("}") != -1)
                {
                    this->location.push_back(loc);
                    loc.~LocaTion();
                    break;
                }
                else
                {
                    if (vect[i].find("index") != -1)
                    {
                        if (get_key(vect[i]) == "index")
                            loc.setindex(get_value(vect[i]));
                    }
                    if (vect[i].find("auto_index") != -1)
                    {
                        if (get_key(vect[i]) == "auto_index")
                            loc.setauto_index(get_value(vect[i]));
                    }
                    if (vect[i].find("allow_methods") != -1)
                    {
                        if (get_key(vect[i]) == "allow_methods")
                            loc.setallow_methods(get_value(vect[i]));
                    }
                    if (vect[i].find("return") != -1)
                    {
                        if (get_key(vect[i]) == "return")
                            loc.set_return(get_value(vect[i]));
                    }
                    if (vect[i].find("fastcgi_pass") != -1)
                    {
                        if (get_key(vect[i]) == "fastcgi_pass")
                            loc.setfascgi_pass(get_value(vect[i]));
                    }
                    if (vect[i].find("upload_methods") != -1)
                    {
                        if (get_key(vect[i]) == "upload_methods")
                            loc.setupload_methods(get_value(vect[i]));
                    }
                    if (vect[i].find("upload_store") != -1)
                    {
                        if (get_key(vect[i]) == "upload_store")
                            loc.setupload_store(get_value(vect[i]));
                    }
                    if (vect[i].find("name") != -1)
                    {
                        if (get_key(vect[i]) == "name")
                            loc.setname(get_value(vect[i]));
                    }
                    if (vect[i].find("root") != -1)
                    {
                        if (get_key(vect[i]) == "root")
                            loc.setroot(get_value(vect[i]));
                    }
                }
                i++;
            }
        }
        i++;
    }
}
