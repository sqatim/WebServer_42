/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/05 13:41:16 by amine            ###   ########.fr       */
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
    typedef std::map<std::string, std::string> FreqMap;
    std::string word;
    FreqMap wf;
    std::ifstream infile("webserv.conf");
    std::fstream file;
    std::string  t, q, filename;
    filename = "webserv.conf";
    file.open(filename.c_str());
    while (file >> word)
    {
        // std::cout << "{" << word << "}"<<std::endl;
        std::string key = word;
        file >> word;
        wf[key] = word;
    }
    for (FreqMap::iterator it = wf.begin(); it != wf.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
}

int main()
{
    CountWords4();
    return 0;
}