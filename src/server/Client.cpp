#include "server/Client.h"
#include "error.h"
#include <netdb.h>


Client::Client() : _nick("*"), _user("*"), _buffer(), _authenticated(false)
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(int fd) : _fd(fd), _nick("*"), _user("*"), _buffer(), _authenticated(false)
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

/*
Client::Client(const Client &other)
{
	*this = other;
}
*/

Client::~Client()
{
}

/*
Client& Client::operator=(const Client& other)
{
	if (this != &other) {
		_fd = other._fd;
		_sock_addr = other._sock_addr;
		memcpy(_ip, other._ip, NI_MAXHOST);
		_addrlen = other._addrlen;
		_nick = other._nick;
		_user = other._user;
		_real_name = other._real_name;
		_buffer = other._buffer;
		_authenticated = other._authenticated;
		_last_message = other._last_message;
	}
	return *this;
}
*/

int Client::get_fd() const { return _fd; }

const sockaddr_storage* Client::get_storage_addr() const { return &_sock_addr; }

socklen_t* Client::get_addr_len() {	return &_addrlen; }

const char* Client::get_IP() const { return _ip; }

const std::string& Client::get_nick() const { return _nick; }

const std::string& Client::get_user() const { return _user; }

const std::string& Client::get_real_name() const { return _real_name; }

const std::string& Client::get_last_message() const { return _last_message; }

const std::string Client::get_source() const
{
	if (_user.empty())
		return _nick;
	return ":" + _nick + "!" + _user + "@" + get_IP();
}

bool Client::is_authenticated() const {	return _authenticated; }

bool Client::has_given_password() const { return _pwd_ok; }

bool Client::has_given_one_name() const { return _name_given; }

void Client::set_fd(int fd) { _fd = fd; }

void Client::set_IP()
{
	getnameinfo((struct sockaddr *)&_sock_addr, _addrlen, _ip,
			sizeof(_ip), NULL, 0, NI_NUMERICHOST);
}

void Client::set_nick(std::string const new_nick) {	_nick = new_nick; }

void Client::set_user(std::string const new_user) {	_user = new_user; }

void Client::set_real_name(std::string const new_real_name) { _real_name = new_real_name; }

void Client::set_authenticated(const bool value) { _authenticated = value; }

void Client::set_password_ok(const bool value) {	_pwd_ok = value; }

void Client::set_name_given(const bool value) {	_name_given = value; }

int Client::read_buffer() {
	if (_buffer.receive(_fd) <= 0) {
		ERROR("client connection lost or read error");
		return -1;
	}
	if (_buffer.has_message() == -1) {
		if (_buffer.get_length() == BUFFER_SIZE) {
			ERROR("buffer full, erasing it");
			_buffer.clear();
			return 1;
		}
		WARNING("no message yet");
		return 1;
	}
	return 0;
}

int Client::send(std::string const message) const
{
	if (::send(_fd, message.c_str(), message.size(), 0) == -1)
	{
		ERROR("sending message");
		return -1;
	}
	return 0;
}

bool Client::has_message() const
{
	return _buffer.has_message() != -1;
}

std::string Client::extract_message()
{
	return _buffer.extract_message();
}
