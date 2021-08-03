/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/02 18:19:06 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <fstream>

int main()
{
    std::string line;
    std::ifstream myfile("webserv.conf");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::cout << line << std::endl;
        }
    }
    return 0;
}