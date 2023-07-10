/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:36:23 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/10 21:19:52 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Client.h"
#include <netdb.h>


Client::Client()
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(int fd) : _fd(fd)
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(Client &other) : _fd(other._fd), _sock_addr(other._sock_addr)
{
}

Client::~Client()
{
}

Client& Client::operator=(const Client& other)
{
	if (this != &other) {
		_fd = other._fd;
	}
	return *this;
}

int Client::getFd() const
{
	return _fd;
}

sockaddr_storage* Client::getStorageAddr()
{
	return &_sock_addr;
}

socklen_t* Client::getAddrLen()
{
	return &_addrlen;
}

char const* Client::getIP() const
{
	return _ip;
}

void Client::setFd(int fd)
{
	_fd = fd;
}

void Client::setIPAddr()
{
	getnameinfo((struct sockaddr *)&_sock_addr, _addrlen, _ip,
			sizeof(_ip), NULL, 0, NI_NUMERICHOST);
}
