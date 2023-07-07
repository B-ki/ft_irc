/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:31:57 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/07 17:06:35 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.h"
#include <string.h>
#include <utility>

Server::Server() : _started(false), _sockfd(-1), _port(DEFAULT_PORT),
	_password(DEFAULT_PASSWORD), _ip_version(), _hints(), _servinfo(NULL),
	_client_pfd_list()
{
	INFO((std::string)"no port provided, using default port " + DEFAULT_PORT);
	INFO((std::string)"setting password to the default '" + DEFAULT_PASSWORD + "'");
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _port.c_str(), &_hints, &_servinfo) != 0) {
		ERROR("could not get the server connection details");
		exit(1); // TODO throw an error ??
	}
}

Server::Server(std::string port, std::string password) : _started(false), 
	_sockfd(-1), _port(port), _password(password), _ip_version(), _hints(),
	_servinfo(NULL), _client_pfd_list()
{
	INFO((std::string)"using the given port " + port);
	INFO((std::string)"using the given password '" + port + "'");
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
	for(std::map<int, Client*>::iterator it = _client_list.begin(); 
			it != _client_list.end(); it++)
	{
		delete (*it).second;
	}
	INFO("Destroying server");
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
	int 	yes = 1;
	void*	addr;
	char	ipstr[INET6_ADDRSTRLEN];

	_sockfd = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	if (_sockfd < 0) {
		ERROR("could not creatre server socket");
		return 1;
	}
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		ERROR("can't set socket options");
		return 2;
	}

	if (bind(_sockfd, _servinfo->ai_addr, _servinfo->ai_addrlen) == -1) {
		ERROR("can't bind the socket");
		return 3;
	}
	if (listen(_sockfd, MAX_CONNEXIONS) == -1) {
		ERROR("can't listen to the specified port " + _port);
		exit(6);
	}
	struct sockaddr_in*	ipv4 = (struct sockaddr_in *)_servinfo->ai_addr;
	addr = &(ipv4->sin_addr);
	inet_ntop(_servinfo->ai_family, addr, ipstr, sizeof(ipstr));

	_started = true;

	pollfd server_pfd;
	server_pfd.fd = _sockfd;

	_client_pfd_list.insert(_client_pfd_list.begin(), server_pfd);
	// We need to initialize the vector _client_fd_list or poll won't work

	std::cout << "Server in now waiting for connections on: ";
	std::cout << ipstr << ":" << _port << std::endl;
	return 0;
}

int Server::loop()
{
	int ret_poll = 0;
	DEBUG("Before poll");
	ret_poll = poll(&_client_pfd_list[0], _client_pfd_list.size(), -1);
	DEBUG("After poll");
	if (ret_poll < 0) {
		ERROR("poll error");
		return 0;
	}
	int i = 0;
	for (std::vector<pollfd>::iterator it = _client_pfd_list.begin();
			it != _client_pfd_list.end(); it++)
	{
		std::cout << i++;
		if ((*it).revents & POLLIN) {
			addClient(new Client((*it).fd));
			std::cout << "POLLIN\n";
		}
	}
	std::cout << std::endl;
	return 0;
}

int Server::addClient(Client* client)
{
	_client_list.insert(std::make_pair(client->getFd(), client));
	std::cout << "Adding new client fd = " << client->getFd() << std::endl;
	return 0;
}

int Server::deleteClient(Client* client)
{
	_client_list.erase(client->getFd());
	std::cout << "Removing client fd = " << client->getFd() << std::endl;
	delete client;
	return 0;
}
