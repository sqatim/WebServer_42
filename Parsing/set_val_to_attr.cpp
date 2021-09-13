/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/09/13 22:19:34 by amine            ###   ########.fr       */
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

void get_attributs(std::vector<std::string> vect, Parse  * parse, int server_len, int _begin)
{
    int i = 0;
    int j;
    std::vector <LocaTion> tmp;
    std::vector<std::string> tmp1;
    std::vector<t_ret> tmp2;
    std::vector<int> tmp4;
    i = _begin;
    while (i < vect.size() &&  i < server_len)
    {
        if (vect[i].find("listen") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "listen")
                tmp4.push_back(std::stoi(vect_str[1]));
            parse->setlisten(tmp4);
        }
        if (vect[i].find("server_name") != -1)
        {
            std::vector<std::string> tmp;
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "server_name")
            {
                int k = 1;
                while (k < vect_str.size())
                {
                    tmp.push_back(vect_str[k]);
                    k++;
                }
                parse->setserver_name(tmp);
            }
        }
        if (vect[i].find("index") != -1)
        {
            // std::vector<std::string> tmp;
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "index")
            {
                int k = 1;
                while (k < vect_str.size())
                {
                    tmp1.push_back(vect_str[k]);
                    k++;
                }
                parse->set_Index(tmp1);
            }
        }
        if (vect[i].find("error_page") != -1)
        {
            t_ret ret;
            // std::vector<t_ret> tmp2;
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "error_page")
            {
                j = 1;
                if (vect_str.size() < 4)
                {
                    ret.path = "";
                    ret.redirec = "";
                    ret.redirec = vect_str[1];
                    ret.path = vect_str[2];
                    tmp2.push_back(ret);
                }
                parse->seterror_page(tmp2);
            }
        }
        if (vect[i].find("root") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "root")
                parse->setroot(vect_str[1]);
        }
        if (vect[i].find("client_max_body_size") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "client_max_body_size")
                parse->setclient_max_body_size(vect_str[1]);
        }
        if (vect[i].find("host") != -1)
        {
            // std::cout << "sahbi samir sbe3";
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "host")
                parse->sethost(vect_str[1]);
        }
        std::string str = vect[i];
        
        if (vect[i].find("location") != -1)
        {
            LocaTion loc = LocaTion();
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str.size() == 3)
            {
                loc.setoption(vect_str[1]);
                loc.setname(vect_str[2]);
            }
            else
                loc.setname(vect_str[1]);
            while (i < vect.size())
            {
                if (vect[i].find("}") != -1)
                {
                    tmp.push_back(loc);
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
                        {
                            if (vect_str[1].find("GET") != -1)
                            {
                                // std::cout << true << std::endl;
                                loc.set_GET(1);
                            }
                            if (vect_str[1].find("POST") != -1)
                                loc.set_POST(1);
                            if (vect_str[1].find("DELET") != -1)
                                loc.set_DELET(1);
                        }
                        loc.setallow_methods(vect_str[1]);
                        // std::cout << vect_str[1] << "}" << std::endl;
                    }
                    if (vect[i].find("return") != -1)
                    {
                        t_ret ret;
                        std::vector<t_ret> tmp;
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "return")
                        {
                            j = 1;
                            if (vect_str.size() < 4)
                            {
                                ret.path = "";
                                ret.redirec = "";
                                ret.redirec = vect_str[1];
                                ret.path = vect_str[2];
                                tmp.push_back(ret);
                            }
                        }
                        loc.set_return(tmp);
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
            parse->setlocation(tmp);
        }
        i++;
    }
}
