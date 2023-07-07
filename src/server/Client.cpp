/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:36:23 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/07 16:35:58 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Client.h"

Client::Client()
{
}

Client::Client(int fd) : _fd(fd)
{
}

Client::Client(Client &other) : _fd(other._fd)
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

int Client::getFd()
{
	return _fd;
}
