/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val_to_attr.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 22:25:57 by amine             #+#    #+#             */
/*   Updated: 2021/08/07 23:27:58 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void get_attributs(server * serv, FreqMap wf)
{
    int count_error_page = 0;
    std::unordered_multimap<std::string, std::string>::iterator it;
    for (it = wf.begin() ; it != wf.end() ; ++it)
    {
        std::string nn = get_key(it->first);
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
    }
    serv->setcount_error_page(count_error_page);
    std::string *err = new std::string[count_error_page];
    int k = 0;
    for (it = wf.begin() ; it != wf.end() ; ++it)
    {
        std::string nn = get_key(it->first);
        if (nn == "error_page")
        {
            std::string aa = get_value(it->second);
            // std::cout << aa << std::endl;
            err[k] = aa;
            k++;
        }
    }
    serv->seterror_page(err);
}
