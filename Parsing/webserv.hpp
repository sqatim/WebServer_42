/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 12:21:25 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/02 17:24:46 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "parse.hpp"

class WebServ
{
private:
    std::string filename;
    int count_server;
    std::vector<int> server_end_index;
    std::vector<int> server_begin_index;
    std::vector<Parse> _webserv;
public:
    WebServ(std::string filename);
    void setwebserv(std::vector<Parse> val);
    std::vector<Parse> getwebserv();
    void setserver_end_index(std::vector<int> val);
    std::vector<int> getserver_end_index();
    void setcount_server(int val);
    int getcount_server();
    ~WebServ();
    void count_and_set_index(std::vector<std::string> vect_str);
};



#endif