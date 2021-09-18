/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:02:19 by ahaddad           #+#    #+#             */
/*   Updated: 2021/09/18 12:26:51 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include <string.h>
#include <sys/wait.h>

CGI::CGI(/* args */)
{
    this->executable = "/usr/bin/php-cgi";
}

CGI::~CGI()
{
}

void		 CGI::execute(std::string target)
{
    // target = "../index.php";
    pid_t					pid;
	int						_fd[2];
	char					tmp[65536];
	int						ret = 1;

    _binary = "/Users/ahaddad/goinfre/.brew/bin/php-cgi";
	_fd[0] = dup(STDIN_FILENO);
	_fd[1] = dup(STDOUT_FILENO);
	FILE	*input_tmpfile = tmpfile();
	FILE	*output_tmpfile = tmpfile();
	int		input_fd = fileno(input_tmpfile);
	int		output_fd = fileno(output_tmpfile);

    pid = fork();
	if (pid == -1)
	{
		std::cout << "error in fork" << std::endl;
		return ;
	}
    else if (pid == 0)
	{
		char **tab = new char * [3];
		tab[0] = new char [_binary.length() + 1];
		tab[1] = new char [target.length() + 1];
		dup2(output_fd, STDOUT_FILENO);
		dup2(input_fd, STDIN_FILENO);
		strcpy(tab[0], _binary.c_str());
		strcpy(tab[1], target.c_str());
		tab[2] = NULL;
		if (execve(_binary.c_str(), tab, this->Maptomatrice(map)) == -1)
			std::cout << "command not found" << std::endl;
    }
    else
	{
		waitpid(-1, NULL, 0);
		lseek(output_fd, 0, SEEK_SET);

		while (ret > 0)
		{
			memset(tmp, 0, 65536);
			ret = read(output_fd, tmp, 65536 - 1);
			_output += tmp;
		}
		close(output_fd);
		close(input_fd);
	}
}

char		 **CGI::Maptomatrice(MyMap map)
{
	char				  **ret;
	std::string		 tmp;
	size_t				  i;

	i = 0;
	ret = new char* [map.size() + 1];
	for (MyMap::iterator it = map.begin(); it != map.end(); it++)
	{
		// std::cout << it->first << " === > " << it->second << std::endl;
		tmp = it->first + "=" + it->second;
		ret[i] = new char [tmp.length() + 1];
		strcpy(ret[i], tmp.c_str());
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void CGI::set_value_to_maymap()
{
    map["HTTP_ACCEPT_ENCODING"] = "gzip, deflate";
    map["HTTP_ACCEPT_LANGUAGE"] = "en-US,en;q=0.5";
    map["HTTP_CACHE_CONTROL"] = "max-age=0";
    map["HTTP_CONNECTION"] = "keep-alive";
    map["HTTP_SEC_FETCH_DEST"] = "document";
    map["HTTP_SEC_FETCH_MODE"] = "navigate";
    map["HTTP_SEC_FETCH_SITE"] = "same-origin";
    map["HTTP_SEC_FETCH_USER"] = "?1";
    map["HTTP_IF_MODIFIED_SINCE"] = "Tue, 14  Sep 2021 11:47:07 GMT";
    map["HTTP_UPGRADE_INSECURE_REQUESTS"] = "1";
    map["HTTP_USER_AGENT"] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:92.0) Gecko/20100101 Firefox/92.0";
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

std::string CGI::get_outpout()
{
    return _output;
}