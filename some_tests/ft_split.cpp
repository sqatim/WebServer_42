/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:15:58 by amine             #+#    #+#             */
/*   Updated: 2021/08/04 18:22:24 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int count_spaces(std::string s)
{
    int count = 0;

    for (int i = 0; i < s.size(); i++)
        if (s[i] == ' ') count++;
    return count;
}


std::string *ft_split(std::string amine, char c)
{
    int count = count_spaces(amine);
    std::string *ret_split = new std::string[count + 1];
    int i = 0;
    while (i < count + 1)
    {
        int to_find = amine.find(' ');
        ret_split[i] = amine.substr(0, to_find);
        amine = amine.substr(to_find + 1, amine.length());
        i++;
    }
    return ret_split;
}
