/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:21:25 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/01 22:02:43 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "parse.hpp"

class WebServ
{
private:
    std::vector<Parse> _webserv;
public:
    WebServ(/* args */);
    void setwebserv(std::vector<Parse> val);
    std::vector<Parse> getwebserv();
    ~WebServ();
};

#endif