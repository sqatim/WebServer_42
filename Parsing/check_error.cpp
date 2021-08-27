/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:49:42 by amine             #+#    #+#             */
/*   Updated: 2021/08/25 17:18:58 by amine            ###   ########.fr       */
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


int check_keys(FreqMap wf)
{
    std::unordered_multimap<std::string, std::string>::iterator it;
    for (it = wf.begin(); it != wf.end(); ++it)
    {
        std::string nn = get_key(it->first);
        if (nn != "root" && nn != "server_name" && nn != "host" && nn != "client_max_body_size" 
            && nn != "error_page" && nn != "location" && nn != "location" && nn != "index" 
            && nn != "autoindex" && nn != "allow_methods" && nn != "\n" && nn != "return"
            && nn != "fastcgi_pass" && nn != "upload_methods" && nn != "upload_store" && nn != "listen"
            && nn != "error_page" && nn != "")
        {
            return 0;
        }
    }
    return 1;
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