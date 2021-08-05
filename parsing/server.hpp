/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:24:53 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/04 18:37:07 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <map>

class server
{
private:
public:
    std::map<std::string, std::string> my_map;
    server(/* args */);
    ~server();
};
// std::string *ft_split(std::string amine, char c);


#endif