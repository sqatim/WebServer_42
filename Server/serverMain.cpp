/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverMain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:20:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/31 12:57:44 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <arpa/inet.h>
#include "Server.class.hpp"

int main()
{
    // try
    // {
        Parse parse("webserv.conf");
        std::cout << parse;
        // Server server(parse);
    //     server.manipulation(parse);
    // }
    // catch(std::string error)
    // {
    //     std::cout << error << std::endl;
    // }
    return (0);
}
