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


Buffer::Buffer() : _str(), _length(0)
{
}

Buffer::Buffer(const Buffer& other) : _length(other._length)
{
	std::strcpy(_str, other._str);
}

Buffer::~Buffer()
{
}

Buffer& Buffer::operator=(const Buffer& other)
{
	if (this != &other) {
		std::strcpy(_str, other._str);
		_length = other._length;
	}
	return *this;
}

int Buffer::get_length() const { return _length; }

int Buffer::receive(int fd)
{
	int ret = recv(fd, _str + _length, BUFFER_SIZE - _length, 0);
	if (ret <= 0) {
		if (ret == 0) {
			ERROR("fd disconnected");
		}
		else {
			ERROR("recv error");
		}
		return ret;
	}
	_length += ret;
	_str[_length] = '\0';
	return ret;
}

int Buffer::is_message_over()
{
	for (int i = 0; i < _length; i++)
	{
		if (_str[i] == '\n')
			return i;
	}
	return -1;
}

std::string Buffer::get_message(int index)
{
	return std::string(_str, index);
}

void Buffer::flush_message(int index)
{
	_length -= index + 1;
	if (_length < 0) {
		ERROR("bad index in flush_message");
		return;
	}
	std::memmove(_str, _str + index + 1, _length);
	_str[_length] = '\0';
}

void Buffer::clear()
{
	_length = 0;
	_str[0] = '\0';
}
