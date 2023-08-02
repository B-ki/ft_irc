#include "server/Buffer.h"
#include "server/Server.h"


Buffer::Buffer() : _str(), _length(0) {}

Buffer::Buffer(const Buffer& other) : _length(other._length)
{ std::strcpy(_str, other._str); }

Buffer& Buffer::operator=(const Buffer& other)
{
	if (this != &other) {
		std::strcpy(_str, other._str);
		_length = other._length;
	}
	return *this;
}

Buffer::~Buffer() {}

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

int Buffer::has_message() const
{
	for (int i = 0; i < _length; i++)
	{
		if (_str[i] == '\n')
			return i;
	}
	return -1;
}

std::string Buffer::extract_message()
{
	int index = has_message();
	if (index == -1)
		return "";
	std::string message(_str, index);
	if (message.size() > 1 && message[message.size() - 1] == '\r')
		message.erase(message.size() - 1);
	_length -= index + 1;
	std::memmove(_str, _str + index + 1, _length);
	_str[_length] = '\0';
	return message;
}

void Buffer::clear()
{
	_length = 0;
	_str[0] = '\0';
}
