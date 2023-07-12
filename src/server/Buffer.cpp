/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:12:03 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/12 19:29:52 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Buffer.h"
#include "server/Server.h"


Buffer::Buffer() : _s()
{
}

Buffer::Buffer(const Buffer& other)
{
	std::strcpy(_s, other._s);
}

Buffer::~Buffer()
{
}

Buffer& Buffer::operator=(const Buffer& other)
{
	if (this != &other)
		std::strcpy(_s, other._s);
	return *this;
}

char* Buffer::get_buffer()
{
	return _s;
}

int Buffer::receive(const int fd)
{
	int ret = recv(fd, _s, BUFFER_SIZE, 0);
	return ret;
}
