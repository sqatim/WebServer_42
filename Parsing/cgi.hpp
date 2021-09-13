/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:01:44 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/13 16:32:34 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
#include <map>
#include "../Server/headers/Request.class.hpp"

typedef	std::map<std::string, std::string>	mymap;
class cgi
{
private:
    int				_stdin;
	int				_stdout;
    std::string		_binary;
	std::string		_output;
	std::string		_input;

public:
    cgi(/* args */);
    void		 execute(std::string target);
    ~cgi();
};





#endif