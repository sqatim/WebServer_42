/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/06 14:08:39 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void CountWords4(void)
{
    typedef std::multimap<std::string, std::string> FreqMap;
    std::string word;
    FreqMap wf;
    std::ifstream infile("webserv.conf");
    std::fstream file;
    std::string filename;
    filename = "webserv.conf";
    file.open(filename.c_str());
    while (file >> word)
    {
        if (word == "server" || word == "}" || word == "{")
            continue;
        std::string key = word;
        file >> word;
        wf.insert(std::pair<std::string , std::string>(key, word));
    }
    for (FreqMap::iterator it = wf.begin(); it != wf.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
}

int main()
{
    
    CountWords4();
    return 0;
}