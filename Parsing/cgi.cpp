/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:02:19 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/15 14:08:41 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

CGI::CGI(/* args */)
{
    this->executable = "/usr/bin/php-cgi";
}

CGI::~CGI()
{
}

void		 CGI::execute(std::string target)
{
    target = "index.php";
    pid_t pid;
    int fd[2];
    int ret(1);
}

void CGI::set_value_to_maymap()
{
    // map["HTTP_ACCEPT_ENCODING"] = "gzip, deflate";
    // map["HTTP_ACCEPT_LANGUAGE"] = "en-US,en;q=0.5";
    // map["HTTP_CACHE_CONTROL"] = "max-age=0";
    // map["HTTP_CONNECTION"] = "keep-alive";
    // map["HTTP_SEC_FETCH_DEST"] = "document";
    // map["HTTP_SEC_FETCH_MODE"] = "navigate";
    // map["HTTP_SEC_FETCH_SITE"] = "same-origin";
    // map["HTTP_SEC_FETCH_USER"] = "?1";
    // map["HTTP_IF_MODIFIED_SINCE"] = "Tue, 14  Sep 2021 11:47:07 GMT";
    // map["HTTP_UPGRADE_INSECURE_REQUESTS"] = "1";
    // map["HTTP_USER_AGENT"] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:92.0) Gecko/20100101 Firefox/92.0";
    map["AUTH_TYPE"] = "";
    map["CONTENT_LENGTH"] = "0";
    map["CONTENT_TYPE"] = "text.html";
    map["DOCUMENT_ROOT"] = "./www/cgi";
    map["GATEWAY_INTERFACE"] = "CGI/1.1";
    map["HTTP_ACCEPT"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8";
    map["HTTP_HOST"] = "127.0.0.1:8002";
    map["HTTP_REFERER"] = "http://127.0.0.1:8002/cgi/";
    map["PATH_INFO"] = "/cgi/index.php";
    map["PATH_TRANSLATED"] = "./www/cgi/index.php";
    map["QUERY_STRING"] = "";
    map["REDIRECT_STATUS"] = "200";
    map["REMOTE_ADDR"] = "127.0.0.1";
    map["REMOTE_USER"] = "user";
    map["REQUEST_METHOD"] = "GET";
    map["REQUEST_URI"] = "/cgi/index.php";
    map["SCRIPT_NAME"] = "/usr/bin/php-cgi";
    map["SERVER_NAME"] = "default_server";
    map["SERVER_PORT"] = "8002";
    map["SERVER_PROTOCOL"] = "HTTP/1.1";
    map["SERVER_SOFTWARE"] = "webserv/1.0";
}