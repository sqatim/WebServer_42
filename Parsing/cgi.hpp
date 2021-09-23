/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:01:44 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/22 16:42:54 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
#include <map>
#include "../Server/headers/Request.class.hpp"

typedef	std::map<std::string, std::string>	MyMap;
class CGI
{
private:
    MyMap           map;
    std::string     executable;
    int				_stdin;
	int				_stdout;
    std::string		_binary;
	std::string		_output;
	std::string		_input;

public:
    CGI(/* args */);
    char		 **Maptomatrice(MyMap param);
    void execute(std::string target);
    void set_value_to_maymap(Request m_request);
    std::string get_outpout();
    ~CGI();
};





#endif