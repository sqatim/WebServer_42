/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 22:35:12 by amine             #+#    #+#             */
/*   Updated: 2021/10/05 10:46:41 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"
#include "location.hpp"

LocaTion::LocaTion(/* args */)
{
    this->auto_index = "";
    this->allow_methods = "";
    this->fastcgi_pass = "";
    this->upload_methods = "";
    this->upload_store = "";
    this->name = "";
    this->root = "";
    this->option = "";
    this->get = 1;
    this->post = 0;
    this->delet = 0;
}

LocaTion::~LocaTion()
{
}

LocaTion::LocaTion(const LocaTion &src)
{
    this->index = src.index;
    this->auto_index = src.auto_index;
    this->allow_methods = src.allow_methods;
    this->_return = src._return;
    this->fastcgi_pass = src.fastcgi_pass;
    this->upload_methods = src.upload_methods;
    this->upload_store = src.upload_store;
    this->name = src.name;
    this->root = src.root;
    this->option = src.option;
    this->get = src.get;
    this->post = src.post;
    this->delet = src.delet;
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
    this->root = src.root;
    this->option = src.option;
    this->get = src.get;
    this->post = src.post;
    this->delet = src.delet;
    return *this;
}

void LocaTion::setindex(std::vector<std::string> val)
{
    size_t i = 0;
    index.clear();
    while (i < val.size())
    {
        this->index.push_back(val[i]);
        i++;
    }
}
std::vector<std::string> LocaTion::getindex()
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
void LocaTion::set_return(std::vector<t_ret> val)
{
    size_t i = 0;
    _return.clear();
    while (i < val.size())
    {
        this->_return.push_back(val[i]);
        i++;
    }
    // this->_return = val;
}
std::vector<t_ret> LocaTion::get_return()
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
void LocaTion::setoption(std::string val)
{
    this->option = val;
}
std::string LocaTion::getoption()
{
    return this->option;
}

// std::string LocaTion::getenable_upload()
// {
//     return (this->upload_methods);
// }
void LocaTion::set_GET(int val)
{
    get = val;
}
int LocaTion::get_GET()
{
    return get;
}
void LocaTion::set_POST(int val)
{
    post = val;
}
int LocaTion::get_POST()
{
    return post;
}
void LocaTion::set_DELET(int val)
{
    delet = val;
}
int LocaTion::get_DELET()
{
    return delet;
}