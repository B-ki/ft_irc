/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:31:57 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/06 19:56:47 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.h"
#include <string.h>

Server::Server()
{
	INFO((std::string)"no port provided, using default port " + DEFAULT_PORT);
	_port = DEFAULT_PORT;
	INFO((std::string)"setting password to the default '" + DEFAULT_PASSWORD + "'");
	_password = DEFAULT_PASSWORD;
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _port.c_str(), &_hints, &_servinfo) != 0) {
		ERROR("could not get the server connection details");
		exit(1); // TODO throw an error ??
	}
}

Server::Server(std::string port, std::string password)
{
	INFO((std::string)"using the given port " + port);
	_port = port;
	INFO((std::string)"using the given password '" + port + "'");
	_password = password;
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _port.c_str(), &_hints, &_servinfo) != 0) {
		ERROR("could not get the server connection details");
		exit(1); // TODO throw an error ??
	}
}

Server::Server(const Server& server)
{
	*this = server;
}

Server&	Server::operator=(const Server& server)
{
	if (this != &server) {
		_port = server._port;
		_hints = server._hints;
		_servinfo = server._servinfo;
		_sockfd = server._sockfd;
		_started = server._started;
	}
	return *this;
}

Server::~Server()
{
	this->stop();
	freeaddrinfo(_servinfo);
}

int	Server::stop()
{
	if (_started) {
		INFO("stopping the server");
		close(_sockfd);
		return 0;
	} else {
		INFO("could not stop the server, wasn't running");
		return -1;
	}
}

int Server::start()
{
	_sockfd = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	if (_sockfd < 0) {
		ERROR("Can't create socket from servinfo");
		exit(1);
	}

		

}
