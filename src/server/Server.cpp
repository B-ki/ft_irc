/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:31:57 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/12 19:33:10 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.h"
#include "color.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
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
	server_pfd.events = POLLIN;

	_client_pfd_list.insert(_client_pfd_list.begin(), server_pfd);
	std::cout << "Server socket " << _sockfd << " added to _client_pfd_list\n";
	// We need to initialize the vector _client_fd_list or poll won't work

	std::cout << "Server in now waiting for connections on: ";
	std::cout << ipstr << ":" << _port << std::endl;
	return 0;
}

int Server::loop()
{
	int ret_poll = 0;
	ret_poll = poll(&_client_pfd_list[0], _client_pfd_list.size(), -1);
	if (ret_poll < 0) {
		ERROR("poll error");
		return 0;
	}
	int listener = _client_pfd_list.begin()->fd;
	for(size_t i = 0; i < _client_pfd_list.size(); i++)
	{
		if (_client_pfd_list[i].revents & POLLIN) {
			std::cout << "POLLIN from fd = " << _client_pfd_list[i].fd << std::endl;
			if (_client_pfd_list[i].fd == listener) {
				if (create_client() != 0) {
					ERROR("Can't add client");
					return 1;
				}
			} else {
				int nbytes = recv(_client_pfd_list[i].fd, _buffer, BUFFER_SIZE, 0);
				std::cout << GREEN << "nbytes = " << RESET << nbytes << std::endl;
				if (nbytes <= 0 || nbytes >= BUFFER_SIZE) {
					if (nbytes == 0) 
						delete_client(&_client_pfd_list[i]);
					else {
						ERROR("Error recv");
						return 2;
					}
				} else {
					for (std::vector<pollfd>::iterator it2 = _client_pfd_list.begin();
							it2 != _client_pfd_list.end();
							it2++)
					{
						if (it2->fd != listener && it2->fd != _client_pfd_list[i].fd) {
							if (send(it2->fd, _buffer, nbytes, 0) == -1) {
								ERROR("Error send");
								return 3;
							}
						}
					}
				}
				// process buffer
					
			}
		}
	}
	return 0;
}

int Server::create_client()
{
	Client client;
	struct sockaddr* ptr = (struct sockaddr *)client.get_storage_addr();
	int client_fd = accept(_sockfd, ptr, client.get_addr_len()); 
	if (client_fd == -1) {
		ERROR("accept error, client deleted");
		return 1;
	}

	// Adding the new client to the Client list
	client.set_fd(client_fd);
	client.set_IP();
	_client_list.insert(std::make_pair(client_fd, client));

	// Adding the new client to the poll_fds_list
	pollfd new_client;
	new_client.fd = client_fd;
	new_client.events = POLLIN;
	_client_pfd_list.push_back(new_client);

	// Printing
	if (client.get_storage_addr()->ss_family == AF_INET ||
			client.get_storage_addr()->ss_family == AF_INET6) {
		std::cout << "Adding new client fd : " << client.get_fd();
		std::cout << ", IP : " << client.get_IP() << std::endl;
	}
	print_client();
	return 0;
}

int Server::delete_client(struct pollfd* ptr)
{
	int client_fd = ptr->fd;
	std::vector<pollfd>::iterator it(ptr); 
	Client& client = _client_list.find(client_fd)->second; 
	std::cout << "Removing client fd : " << client_fd; 
	std::cout << ", IP : " << client.get_IP() << std::endl;
	_client_list.erase(client.get_fd());
	_client_pfd_list.erase(it);
	close(client_fd);
	print_client();
	return 0;
}

void Server::print_client()
{
	std::cout << std::endl;
	std::cout << std::setw(25) << std::setfill(' ');
	std::cout << std::string(26, '-') << "\n";
	std::cout << std::setw(25) << std::setfill(' ') << std::left << "|     CLIENT LIST";
	std::cout << "|\n";
	std::cout << std::string(26, '-') << "\n";
	std::cout << std::setw(22) << std::setfill(' ') << std::left << "| Listener : " << _client_pfd_list[0].fd;
	std::cout << "  |\n";
	std::cout << std::string(26, '-') << "\n";
	for (size_t i = 1; i < _client_pfd_list.size(); i++) {
		std::cout << std::setw(22) << std::setfill(' ') << std::left << "| Client : " << _client_pfd_list[i].fd;
		std::cout << "  |\n";
		std::cout << std::string(26, '-') << "\n";
	}
	std::cout << std::endl;
}

void Server::process_buffer()
{
	std::string raw(_buffer);
	Message msg(raw);
}

int Server::execute_cmd(const Message& msg)
{
	switch (msg.get_cmd()) {
		case PASS:
			break;
		case NICK:
			break;
		case USER:
			break;
		case JOIN:
			break;
		case PART:
			break;
		case LEAVE:
			break;
		case PRIVMSG:
			break;
		case QUIT:
			break;
		case KICK:
			break;
		case INVITE:
			break;
		case TOPIC:
			break;
		case MODE:
			break;
		case NOTHING:
			break;
	}
	
	return 0;
}

Client& Server::get_client(int const fd) 
{
	return (*_client_list.find(fd)).second;
}

Client& Server::get_client(std::string const nick) 
{
	for (std::map<int, Client>::iterator it = _client_list.begin();
			it != _client_list.end(); it++)
	{
		if ((*it).second.get_nick() == nick)
			return (*it).second;
	}
	// Throw exception if fail -> Check required for every command using nick namme
	// Ex : PRIVMSG John blablabla -> check first if John exist or not
	return (*_client_list.begin()).second;
}

