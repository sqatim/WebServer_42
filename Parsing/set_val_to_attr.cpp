/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/10/03 14:31:47 by ahaddad          ###   ########.fr       */
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

int check_is_digit(std::string str)
{
    int i = 0;
    while (i < str.length())
    {
        if (std::isdigit(str[i]) == 0)
            return -1;
        i++;
    }
    return 1;
}

int check_listen(std::vector<std::string> vect_str)
{
    if (vect_str.size() == 1)
        return -1;
    if (vect_str[0] != "listen")
        return -1;
    int i = 1;
    while (i < vect_str.size())
    {
        if (check_is_digit(vect_str[i]) == -1)
            return -1;
        i++;
    }
    return 1;
}



int check_error_page(std::vector<std::string> vect_str)
{
    if (vect_str.size() != 3)
        return -1;
    if (vect_str[0] != "error_page")
        return -1;
    if (check_is_digit(vect_str[1]) == -1)
        return -1;
    return 1;
}

int check_index(std::vector<std::string> vect_str)
{
    if (vect_str.size() != 2)
        return -1;
    if (vect_str[1] != "on" && vect_str[1] != "off")
        return -1;
    return 1;
}

int check_client_max_body_size(std::vector<std::string> vect_str)
{
    if (vect_str.size() != 2)   
        return -1;
    if (vect_str[0] != "client_max_body_size")
        return -1;
    if (vect_str[1][vect_str[1].length()-1] != 'm')
        return -1;
    int i = 0;
    while (i < (vect_str[1].length() -1))
    {
        if (std::isdigit(vect_str[1][i]) == 0)
            return -1;
        i++;
    }
    return 1;
}

int check_host(std::vector<std::string> vect_str)
{
    if (vect_str.size() != 2)
        return -1;
    if (vect_str[0] != "host")
        return -1;
    std::vector<std::string> vect = splitstring_with_point(vect_str[1], ".");
    int i = 0;
    if (vect_str[1][0] == '.' || vect_str[1][vect_str[1].length() -1] == '.')
        return -1;
    while (i < vect_str[1].length())
    {
        if (vect_str[1][i] == '.')
        {
            i++;
            if (i < vect_str[1].length())
                if (vect_str[1][i] == '.')
                    return -1;
        }
        i++;
    }
    if (vect.size() != 4)
        return -1;
    i = 0;
    while (i < vect.size())
    {
        if (check_is_digit(vect[i]) == -1)
            return -1;
        i++;
    }
    i = 0;
    while (i < vect.size())
    {
        if (std::stoi(vect[i]) > 255)
            return -1;
        i++;
    }
    return 1;
}

int check_return(std::vector<std::string> vect_str)
{
    if (vect_str.size() != 3)
        return -1;
    if (vect_str[0] != "return")
        return -1;
    if (check_is_digit(vect_str[1]) == -1)
        return -1;
    return 1;
}


int get_attributs(std::vector<std::string> vect, Parse  * parse, int server_len, int _begin)
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
            if (check_listen(vect_str) == -1)
                return -1;
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
            if (check_index(vect_str) == -1)
                return -1;
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
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (check_error_page(vect_str) == -1)
                return -1;
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
        if (vect[i].find("root") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str[0] == "root")
                parse->setroot(vect_str[1]);
        }
        if (vect[i].find("client_max_body_size") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (check_client_max_body_size(vect_str) == -1)
                return -1;
            if (vect_str[0] == "client_max_body_size")
                parse->setclient_max_body_size(vect_str[1]);
        }
        if (vect[i].find("host") != -1)
        {
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (check_host(vect_str) == -1)
                return -1;
            parse->sethost(vect_str[1]);
        }
        std::string str = vect[i];
        
        if (vect[i].find("location") != -1)
        {
            LocaTion loc = LocaTion();
            std::vector<std::string> vect_str = splitstring(vect[i], " ");
            if (vect_str.size() == 2)
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
                        if (check_index(vect_str) == -1)
                            return -1;
                        if (vect_str[0] == "index")
                        {
                            vect_str.erase(vect_str.begin());
                            loc.setindex(vect_str);
                        }
                    }
                    if (vect[i].find("auto_index") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (check_index(vect_str) == -1)
                            return -1;
                        if (vect_str[0] == "auto_index")
                            loc.setauto_index(vect_str[1]);
                    }
                    if (vect[i].find("allow_methods") != -1)
                    {
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (vect_str[0] == "allow_methods")
                        {
                            loc.set_GET(0);
                            loc.set_POST(0);
                            loc.set_DELET(0);
                            if (vect_str[1].find("GET") != -1)
                                loc.set_GET(1);
                            if (vect_str[1].find("POST") != -1)
                                loc.set_POST(1);
                            if (vect_str[1].find("DELET") != -1)
                                loc.set_DELET(1);
                        }
                        loc.setallow_methods(vect_str[1]);
                    }
                    if (vect[i].find("return") != -1)
                    {
                        t_ret ret;
                        std::vector<t_ret> tmp;
                        std::vector<std::string> vect_str = splitstring(vect[i], " ");
                        if (check_return(vect_str) == -1)
                            return -1;
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
    return 1;
}
