/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 19:26:05 by amine             #+#    #+#             */
/*   Updated: 2021/10/05 11:04:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void error(std::string str)
{
    std::cout << str << std::endl;
    exit(0);
}

int is_printable(std::string str)
{
    size_t i = 0;
    while (i < str.size())
    {
        if (isprint(str[i]))
            return 1;
        i++;
    }
    return 0;
}

int CountWords(std::string str)
{
    size_t i = 0;
    int countword = -1;
    while (i < str.length())
    {
        if (str[i] == ' ')
            i++;
        else
            break;
    }
    size_t end = str.length() - 1;
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
            i++;
        if (str[i] == ' ' && str[i + 1] != ' ')
            countword++;
        i++;
    }
    return countword;
}

std::string get_key(std::string str)
{
    std::string ret;
    size_t i = 0;
    int j = 0;
    size_t k = 0;
    while (i < str.length())
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
            break;
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
            break;
    }
    ret = str.substr(i, j);
    return ret;
}
std::string get_value(std::string str)
{
    std::string ret;
    std::string key = get_key(str);
    int found = str.find(key);
    found += key.length();
    ret = str.substr(found, str.length() - found);
    return ret;
}

std::string get_key_tab(std::string str)
{
    std::string ret;
    size_t i = 0;
    int j = 0;
    size_t k = 0;
    while (i < str.length())
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
            break;
    }
    j = 0;
    k = i;
    while (k < str.length())
    {
        if (str[k] != '\t')
        {
            j++;
            k++;
        }
        else
            break;
    }
    ret = str.substr(i, j);
    return ret;
}

std::vector<std::string> splitstring_with_point(std::string str, std::string to_split_with)
{
    std::vector<std::string> vect_str;
    size_t start = 0;
    while (start < str.size())
    {
        if (str[start] != '\t' && str[start] != ' ')
            break;
        start++;
    }
    std::string _str = str.substr(start, str.length());
    to_split_with = ".";
    start = 0;
    int end = _str.find(to_split_with);
    while (end != -1)
    {
        if (_str.substr(start, end - start).length() > 0)
            vect_str.push_back(_str.substr(start, end - start));
        start = end + to_split_with.size();
        end = _str.find(to_split_with, start);
    }
    vect_str.push_back(_str.substr(start, end - start));
    size_t i = 0;
    while (i < vect_str.size())
    {
        if (vect_str[i].length() == 0)
            vect_str.erase(vect_str.begin() + i);
        i++;
    }
    return vect_str;
}

std::vector<std::string> splitstring(std::string str, std::string to_split_with)
{
    std::vector<std::string> vect_str;
    size_t start = 0;
    while (start < str.size())
    {
        if (str[start] != '\t' && str[start] != ' ')
            break;
        start++;
    }
    std::string _str = str.substr(start, str.length());
    to_split_with = " ";
    start = 0;
    int end = _str.find(to_split_with);
    while (end != -1)
    {
        if (_str.substr(start, end - start).length() > 0)
            vect_str.push_back(_str.substr(start, end - start));
        start = end + to_split_with.size();
        end = _str.find(to_split_with, start);
    }
    vect_str.push_back(_str.substr(start, end - start));
    size_t i = 0;
    while (i < vect_str.size())
    {
        // std::string str  = get_key_tab
        // vect_str[i] = get_key_tab(vect_str[i]);
        if (vect_str[i].length() == 0)
            vect_str.erase(vect_str.begin() + i);
        i++;
    }
    return vect_str;
}