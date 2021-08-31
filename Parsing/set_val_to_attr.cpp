/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/31 17:42:30 by ahaddad          ###   ########.fr       */
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
    int j;
    while (i < vect.size())
    {
        if (vect[i].find("listen") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "listen")
                this->listen.push_back(std::stoi(vect_str[1]));
        }
        if (vect[i].find("server_name") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "server_name")
                this->server_name.push_back(vect_str[1]);
        }
        if (vect[i].find("error_page") != -1)
        {
            t_ret ret;
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            // std::cout << vect_str.size() << std::endl;
            if (vect_str[0] == "error_page")
            {
                j = 1;
                if (vect_str.size() < 4)
                {
                    ret.path = "";
                    ret.redirec = "";
                    ret.redirec = vect_str[1];
                    ret.path = vect_str[2];
                    this->error_page.push_back(ret);
                }
            }
        }
        if (vect[i].find("root") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "root")
                this->root = vect_str[1];
        }
        if (vect[i].find("client_max_body_size") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "client_max_body_size")
                this->client_max_body_size = vect_str[1];
        }
        if (vect[i].find("host") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "return")
                this->host = vect_str[1];
        }
        std::string str = vect[i];
        if (vect[i].find("location") != -1)
        {
            LocaTion loc = LocaTion();
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            loc.setname(vect_str[1]);
            while (i < vect.size())
            {
                if (vect[i].find("}") != -1)
                {
                    this->location.push_back(loc);
                    break;
                }
                else
                {
                    if (vect[i].find("index") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "index")
                        {
                            vect_str.erase(vect_str.begin());
                            loc.setindex(vect_str);
                        }
                    }
                    if (vect[i].find("auto_index") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "auto_index")
                            loc.setauto_index(vect_str[1]);
                    }
                    if (vect[i].find("allow_methods") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "allow_methods")
                            loc.setallow_methods(vect_str[1]);
                    }
                    if (vect[i].find("return") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "return")
                            loc.set_return(vect_str[1]);
                    }
                    if (vect[i].find("fastcgi_pass") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "fastcgi_pass")
                            loc.setfascgi_pass(vect_str[1]);
                    }
                    if (vect[i].find("upload_methods") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "upload_methods")
                            loc.setupload_methods(vect_str[1]);
                    }
                    if (vect[i].find("upload_store") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "upload_store")
                            loc.setupload_store(vect_str[1]);
                    }
                    if (vect[i].find("name") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "name")
                            loc.setname(vect_str[1]);
                    }
                    if (vect[i].find("root") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "root")
                            loc.setroot(vect_str[1]);
                    }
                }
                i++;
            }
        }
        i++;
    }
}
