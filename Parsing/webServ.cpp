/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:23:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/01 22:05:42 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

WebServ::WebServ(/* args */)
{
}

WebServ::~WebServ()
{
}


void WebServ::setwebserv(std::vector<Parse> val)
{
    this->_webserv = val;
}

std::vector<Parse> WebServ::getwebserv()
{
    return this->_webserv;
}