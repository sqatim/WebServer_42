/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:02:19 by ahaddad           #+#    #+#             */
/*   Updated: 2021/10/04 16:21:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include "parse.hpp"
#include <string.h>
#include <sys/wait.h>

CGI::CGI()
{
	this->executable = "/usr/bin/php-cgi";
}

CGI::~CGI()
{
}

void CGI::execute(std::string target, std::string bin)
{
	pid_t pid;
	int _fd[2];
	char tmp[65536];
	int ret = 1;

	_binary = bin;
	_fd[0] = dup(STDIN_FILENO);
	_fd[1] = dup(STDOUT_FILENO);
	FILE *input_tmpfile = tmpfile();
	FILE *output_tmpfile = tmpfile();
	int input_fd = fileno(input_tmpfile);
	int output_fd = fileno(output_tmpfile);
	write(input_fd, _input.c_str(), _input.length());
	lseek(input_fd, 0, SEEK_SET);
	pid = fork();
	if (pid == -1)
	{
		std::cout << "error in fork" << std::endl;
		return;
	}
	else if (pid == 0)
	{
		char **tab = new char *[3];
		tab[0] = new char[_binary.length() + 1];
		tab[1] = new char[target.length() + 1];
		dup2(output_fd, STDOUT_FILENO);
		dup2(input_fd, STDIN_FILENO);
		strcpy(tab[0], _binary.c_str());
		strcpy(tab[1], target.c_str());
		tab[2] = NULL;
		if (execve(_binary.c_str(), tab, this->Maptomatrice(this->map)) == -1)
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
			std::cout << tmp << std::endl;
			_output += tmp;
		}
		close(output_fd);
		close(input_fd);
	}
}

std::vector<std::string> splitstring_with_coma(std::string str, std::string to_split_with)
{
	std::vector<std::string> vect_str;
	int start = 0;
	while (start < str.size())
	{
		if (str[start] != '\t' && str[start] != ' ')
			break;
		start++;
	}
	std::string _str = str.substr(start, str.length());
	// std::cout << _str << std::endl;
	to_split_with = ";";
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
	int i = 0;
	while (i < vect_str.size())
	{
		if (vect_str[i].length() == 0)
			vect_str.erase(vect_str.begin() + i);
		i++;
	}
	return vect_str;
}

void CGI::check_cookie_and_body()
{
	int find_cookie = _output.find("Set-Cookie:");
	int find_Content = _output.find("Content-type");
	std::string str = _output.substr(find_cookie + 11, find_Content - (find_cookie + 11));
	std::vector<std::string> vect = splitstring_with_coma(str, "");
	int i = 0;
	while (i < vect.size())
	{
		std::string tmp = "Set-Cookie: " + vect[i];
		this->_to_set_cookies.push_back(tmp);
		i++;
	}
	int find_doc = _output.find("<!DOCTYPE html>");
	if (find_doc != -1)
		_output = _output.substr(find_doc);
}

char **CGI::Maptomatrice(MyMap map)
{
	char **ret;
	std::string tmp;
	size_t i;

	i = 0;
	ret = new char *[map.size() + 1];
	for (MyMap::iterator it = map.begin(); it != map.end(); it++)
	{
		tmp = it->first + "=" + it->second;
		ret[i] = new char[tmp.length() + 1];
		strcpy(ret[i], tmp.c_str());
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void CGI::set_value_to_maymap(Request m_request)
{
	map["AUTH_TYPE"] = "";
	map["CONTENT_LENGTH"] = m_request.getContentLength();
	map["CONTENT_TYPE"] = "text.html";
	map["DOCUMENT_ROOT"] = "/Users/sqatim/Desktop/WebServer_42/";
	map["GATEWAY_INTERFACE"] = "CGI/1.1";
	map["PATH_INFO"] = m_request.getPath();
	map["PATH_TRANSLATED"] = "/Users/sqatim/Desktop/WebServer_42/Config/login.php";
	map["QUERY_STRING"] = m_request.getquery();
	map["REDIRECT_STATUS"] = "200";
	map["REMOTE_ADDR"] = m_request.getHostSolo();
	map["REQUEST_METHOD"] = m_request.getMethod();
	map["SCRIPT_NAME"] = m_request.getFastCgi();
	map["SERVER_PORT"] = m_request.getPortSolo();
	map["SERVER_PROTOCOL"] = "HTTP/1.1";
	map["SERVER_SOFTWARE"] = "WebsServer/1.0";
	// map["REQUEST_URI"] = m_request.getPath();
	map["HTTP_ACCEPT"] = m_request.getAccept();
	map["HTTP_ACCEPT_ENCODING"] = "gzip, deflate";
	map["HTTP_ACCEPT_LANGUAGE"] = "en-US,en;q=0.5";
	map["HTTP_CACHE_CONTROL"] = "max-age=0";
	map["HTTP_CONNECTION"] = "keep-alive";
	map["HTTP_HOST"] = m_request.getHost();
	map["HTTP_SEC_FETCH_DEST"] = "document";
	map["HTTP_SEC_FETCH_MODE"] = "navigate";
	map["HTTP_SEC_FETCH_SITE"] = "same-origin";
	map["HTTP_SEC_FETCH_USER"] = "?1";
	map["HTTP_UPGRADE_INSECURE_REQUESTS"] = "1";
	map["HTTP_USER_AGENT"] = m_request.getUserAgent();
}

std::string CGI::get_outpout()
{
	return _output;
}

std::vector<std::string> CGI::getto_set_cookies()
{
	return _to_set_cookies;
}