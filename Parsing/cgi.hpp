/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:01:44 by ahaddad           #+#    #+#             */
/*   Updated: 2021/10/05 10:49:33 by sqatim           ###   ########.fr       */
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
    std::string		_binary;
	std::string		_output;
	std::string		_input;
    std::string     Query;
    std::vector<std::string> _to_set_cookies;
public:
    CGI(/* args */);
    char		 **Maptomatrice(MyMap param);
    void execute(std::string target, std::string bin);
    void set_value_to_maymap(Request m_request, std::string root);
    std::string get_outpout();
    std::string get_query();
    std::vector<std::string> getto_set_cookies();
    void check_cookie_and_body();
    ~CGI();
};





#endif