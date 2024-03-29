#include "server/Client.h"
#include "error.h"
#include <netdb.h>
#include <netinet/in.h>


Client::Client() : _fd(-1), _sock_addr(), _ip("0.0.0.0"), _addrlen(),
	_nick("*"), _user("*"), _real_name("*"), _buffer(),
	_authenticated(false), _name_given(false), _pwd_ok(false), _channels()
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(int fd) : _fd(fd), _sock_addr(), _ip("0.0.0.0"), _addrlen(),
	_nick("*"), _user("*"), _real_name("*"), _buffer(),
	_authenticated(false), _name_given(false), _pwd_ok(false), _channels()
{
	memset(&_sock_addr, 0, sizeof(_sock_addr));
	_addrlen = sizeof(struct sockaddr_storage);
}

Client::Client(const Client &other) { *this = other; }

Client::~Client() {}

Client& Client::operator=(const Client& other)
{
	if (this != &other) {
		_fd = other._fd;
		_sock_addr = other._sock_addr;
		memcpy(_ip, other._ip, INET6_ADDRSTRLEN);
		_addrlen = other._addrlen;
		_nick = other._nick;
		_user = other._user;
		_real_name = other._real_name;
		_buffer = other._buffer;
		_authenticated = other._authenticated;
		_name_given = other._name_given;
		_pwd_ok = other._pwd_ok;
		_last_message = other._last_message;
		_channels = other._channels;
	}
	return *this;
}

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

const std::vector<std::string>& Client::get_channels() const { return _channels; }

bool Client::is_authenticated() const {	return _authenticated; }

bool Client::has_given_password() const { return _pwd_ok; }

bool Client::has_given_one_name() const { return _name_given; }

void Client::set_fd(int fd) { _fd = fd; }

void Client::set_IP()
{
	void *addr;

	struct sockaddr_in*	ipv4 = (struct sockaddr_in *)&_sock_addr;
	addr = &(ipv4->sin_addr);
	inet_ntop(AF_INET, addr, _ip, sizeof(_ip));
	//getnameinfo((struct sockaddr *)&_sock_addr, _addrlen, _ip,
	//		sizeof(_ip), NULL, 0, NI_NUMERICHOST);
}

void Client::set_nick(const std::string& new_nick) { _nick = new_nick; }

void Client::set_user(const std::string& new_user) { _user = new_user; }

void Client::set_real_name(const std::string& new_real_name) { _real_name = new_real_name; }

void Client::set_authenticated(const bool value) { _authenticated = value; }

void Client::set_password_ok(const bool value) {	_pwd_ok = value; }

void Client::set_name_given(const bool value) {	_name_given = value; }

void Client::add_channel(const std::string &channel) { _channels.push_back(channel); }

void Client::remove_channel(const std::string &channel)
{
	std::vector<std::string>::iterator it = _channels.begin();
	while (it != _channels.end()) {
		if (*it == channel) {
			_channels.erase(it);
			return;
		}
		++it;
	}
}

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

int Client::send_to(const Client& client, const std::string& message) const
{
	std::stringstream final_message;
	final_message << ":" << get_nick() << "!" << get_user() << "@" << get_IP() << " " << message << "\n";
	if (client.send(final_message.str()) == -1)
		return -1;
	return 0;
}

int Client::reply(const std::string& message, int code) const
{
	std::stringstream final_message;
	if (code < 10) final_message << "0";
	if (code < 100) final_message << "0";
	final_message << code << " " << _nick << " " << message << "\n";
	if (send(final_message.str()) == -1)
		ERROR("sending reply message");
	return code;
}

bool Client::has_message() const { return _buffer.has_message() != -1; }

std::string Client::extract_message() { return _buffer.extract_message(); }

int Client::send(const std::string& message) const
{
	if (::send(_fd, message.c_str(), message.size(), 0) == -1)
	{
		ERROR("cannot send message to client '" + _nick + "'");
		return -1;
	}
	return 0;
}
