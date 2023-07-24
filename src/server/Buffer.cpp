/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:12:03 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/24 21:27:45 by rmorel           ###   ########.fr       */
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

int Buffer::receive(int fd)
{
	int ret = recv(fd, _s + length, BUFFER_SIZE - length, 0);
	if (ret == -1)
		return -1;
	else if (ret == 0)
		return 0;
	else if (ret > 0) {
		length += ret;
		if (get_end_message() < 0)
			return -2;
		ret = length;
		length = 0;
		return ret;
	}
	return ret;
}

int Buffer::get_end_message() const
{
	for (u_int i = 0; i < length; i++)
	{
		if (_s[i] == '\r' && i - 1 < length && _s[i] == '\n')
			return i;
	}
	return -1;	
}
