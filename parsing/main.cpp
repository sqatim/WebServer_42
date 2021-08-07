/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 16:25:41 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/07 23:20:44 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int main()
{
    FreqMap wf;
    std::string word;
    std::ifstream infile("webserv.conf");
    std::fstream file;
    std::string filename;
    std::string name;
    server serv;
    filename = "webserv.conf";
    file.open(filename.c_str());
    while (getline(file ,word))
    {
        int len = CountWords(word);
        if (len > 0)
        {
            wf.insert(std::pair<std::string , std::string>(get_key(word), get_value(word)));
        }
    }
    get_attributs(&serv, wf);
    std::cout << serv.getlisten() << std::endl;
    std::cout << serv.gethost() << std::endl;
    std::cout << serv.getroot() << std::endl;
    std::cout << serv.getserver_name() << std::endl;
    std::cout << serv.getclient_max_body_size() << std::endl;
    int i = 0;
    while (i < serv.getcount_error_page())
    {
        std::cout << serv.geterror_page()[i] << std::endl;
        i++;
    }
    return 0;
}