/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:26:05 by amine             #+#    #+#             */
/*   Updated: 2021/08/07 21:57:34 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int CountWords(std::string str)
{
   int i = 0;
    int countword = 0;
    while (i < str.length())
    {
        if (str[i] == ' ')
            i++;
        else
            break ;
    }
    int end = str.length() - 1;
    while (end > 0)
    {
        if (str[end] == ' ')
            end--;
        else
            break;
    }
    while (i < end)
    {
        if (i == 0 && str[i] == ' ')
            i++ ;
        if (str[i] == ' ' && str[i + 1] != ' ')
            countword++;
        i++; 
    }
    return  countword;
}

std::string     get_key(std::string str)
{
    std::string ret;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < str.length())
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
            break ;
    }
    j = 0;
    k = i;
    while (k < str.length())
    {
        if (str[k] != ' ')
        {
            j++;
            k++;
        }
        else
            break ;
    }
    ret = str.substr(i, j);
    return ret;
}
std::string     get_value(std::string str)
{
    std::string ret;
    std::string key = get_key(str);
    int found = str.find(key);
    found += key.length();
    ret = str.substr(found, str.length() - found);
    return ret;
}