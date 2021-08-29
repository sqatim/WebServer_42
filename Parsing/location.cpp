/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 22:35:12 by amine             #+#    #+#             */
/*   Updated: 2021/08/29 16:45:53 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"
#include "location.hpp"


LocaTion::LocaTion(/* args */)
{
    this->index = "";
    this->auto_index = "";
    this->allow_methods = "";
    this->_return = "";
    this->fastcgi_pass = "";
    this->upload_methods = "";
    this->upload_store = "";
    this->name = "";
    this->root = "";
}

LocaTion::~LocaTion()
{
}

LocaTion::LocaTion(const LocaTion & src)
{
    this->index = src.index;
    this->auto_index = src.auto_index;
    this->allow_methods = src.allow_methods;
    this->_return = src._return;
    this->fastcgi_pass = src.fastcgi_pass;
    this->upload_methods = src.upload_methods;
    this->upload_store = src.upload_store;
    this->name = src.name;
    this->root = src.name;
}

LocaTion &LocaTion::operator=(const LocaTion &src)
{
    this->index = src.index;
    this->auto_index = src.auto_index;
    this->allow_methods = src.allow_methods;
    this->_return = src._return;
    this->fastcgi_pass = src.fastcgi_pass;
    this->upload_methods = src.upload_methods;
    this->upload_store = src.upload_store;
    this->name = src.name;
    this->root = src.name;
    return *this;
}

void LocaTion::setindex(std::string val)
{
    this->index = val;
}
std::string LocaTion::getindex()
{
    return this->index;
}
void LocaTion::setauto_index(std::string val)
{
    this->auto_index = val;
}
std::string LocaTion::getauto_index()
{
    return this->auto_index;
}
void LocaTion::setallow_methods(std::string val)
{
    this->allow_methods = val;
}
std::string LocaTion::getallow_methods()
{
    return this->allow_methods;
}
void LocaTion::set_return(std::string val)
{
    this->_return = val;
}
std::string LocaTion::get_return()
{
    return this->_return;
}
void LocaTion::setfascgi_pass(std::string val)
{
    this->fastcgi_pass = val;
}
std::string LocaTion::getfascgi_pass()
{
    return this->fastcgi_pass;
}
void LocaTion::setupload_methods(std::string val)
{
    this->upload_methods = val;
}
std::string LocaTion::getupload_methods()
{
     return this->upload_methods;
}
void LocaTion::setupload_store(std::string val)
{
    this->upload_store = val;
}
std::string LocaTion::getupload_store()
{
    return this->upload_store;
}
void LocaTion::setname(std::string val)
{
    this->name = val;
}
std::string LocaTion::getname()
{
    return this->name;
}
void LocaTion::setroot(std::string val)
{
    this->root = val;
}
std::string LocaTion::getroot()
{
    return this->root;
}
