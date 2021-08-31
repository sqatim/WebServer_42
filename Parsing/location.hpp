/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:38:37 by ahaddad           #+#    #+#             */
/*   Updated: 2021/08/31 17:31:25 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP
# include "parse.hpp"

typedef struct s_ret
{
    std::string redirec;
    std::string path;
} t_ret;

class LocaTion
{
private:
    std::vector<std::string> index;
    std::string auto_index;
    std::string allow_methods;
    std::string _return;
    std::string fastcgi_pass;
    std::string upload_methods;
    std::string upload_store;
    std::string name;
    std::string root;

    /* data */
public:
    LocaTion(/* args */);
    LocaTion(const LocaTion & src);
    LocaTion &operator=(const LocaTion &f);
    void setindex(std::vector<std::string> val);
    std::vector<std::string> getindex();
    void setauto_index(std::string val);
    std::string getauto_index();
    void setallow_methods(std::string val);
    std::string getallow_methods();
    void set_return(std::string val);
    std::string get_return();
    void setfascgi_pass(std::string val);
    std::string getfascgi_pass();
    void setupload_methods(std::string val);
    std::string getupload_methods();
    void setupload_store(std::string val);
    std::string getupload_store();
    void setname(std::string val);
    std::string getname();
    void setroot(std::string val);
    std::string getroot();
    ~LocaTion();
};

#endif