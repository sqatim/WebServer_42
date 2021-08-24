/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:49:42 by amine             #+#    #+#             */
/*   Updated: 2021/08/15 13:48:08 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

int check_accolades(FreqMap wf, std::string filename)
{
    std::fstream file;
    std::string word;
    int i = 0;

    file.open(filename.c_str());
    while (file >> word)
    {
        if (word == "server")
        {
            file >> word;
            if (word != "{")
                return (1);
        }
        if (word == "{")
            i++;
        if (word == "}")
            i--;
    }
    return i;
}

// int check_keys(FreqMap wf, std::string filename)
// {
//     std::fstream file;
//     std::string word;
//     int i = 0;

//     file.open(filename.c_str());
//     while (file >> word)
//     {
//         if (word == "{")
//             i++;
//         if (word == "}")
//             i--;
//     }
//     return i;
// }