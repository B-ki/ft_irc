/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:36:23 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/12 19:39:24 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Client.h"
#include <netdb.h>


Client::Client() : _nick(), _user(), _buffer()
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(int fd) : _fd(fd), _nick(), _user(), _buffer()
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(const Client &other) : _fd(other._fd), _sock_addr(other._sock_addr),
	_nick(other._nick), _user(other._user),
	_buffer(other._buffer)
{
}

Client::~Client()
{
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) {
		_fd = other._fd;
		_nick = other._nick;
		_user = other._user;
		_buffer = other._buffer;
	}
	return *this;
}

int Client::get_fd() const
{
	return _fd;
}

sockaddr_storage* Client::get_storage_addr()
{
	return &_sock_addr;
}

socklen_t* Client::get_addr_len()
{
	return &_addrlen;
}

char const* Client::get_IP() const
{
	return _ip;
}

std::string Client::get_nick() const
{
	return _nick;
}

std::string Client::get_user() const
{
	return _user;
}

void Client::set_fd(int fd)
{
	_fd = fd;
}

void Client::set_IP()
{
	getnameinfo((struct sockaddr *)&_sock_addr, _addrlen, _ip,
			sizeof(_ip), NULL, 0, NI_NUMERICHOST);
}

void Client::set_nick(std::string const new_nick)
{
	_nick = new_nick;
}

void Client::set_user(std::string const new_user)
{
	_user = new_user;
}
