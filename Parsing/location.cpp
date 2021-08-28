/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 22:35:12 by amine             #+#    #+#             */
/*   Updated: 2021/08/28 22:37:34 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

location::location(/* args */)
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

location::~location()
{
}