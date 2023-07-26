#include "management/Channel.h"
#include "error.h"

Channel::Channel() : _name(), _admins(), _members(), _connected(), _invite_only(false), _topic_restriction(false), _password_activation(false), _password(""), _topic("")
{
}

Channel::Channel(const Client* user, const std::string& name) : _name(name), _admins(), _members(), _connected(), _invite_only(false), _topic_restriction(false), _password_activation(false), _password(""), _topic("")
{
	_admins.push_back(user);
	_members.push_back(user);
}

Channel::Channel(const Channel& other)
{
	*this = other;
}

Channel&    Channel::operator=(const Channel& other)
{
	if (this != &other) {
		_name = other._name;
		_admins = other._admins;
		_members = other._members;
		_connected = other._connected;
		_invite_only = other._invite_only;
		_topic_restriction = other._topic_restriction;
		_password_activation = other._password_activation;
		_password = other._password;
		_topic = other._topic;
	}
	return *this;
}

Channel::~Channel()
{
}

const std::string& Channel::get_name() const
{
	return _name;
}

const std::vector<const Client*>& Channel::get_admins() const
{
	return _admins;
}

const std::vector<const Client*>& Channel::get_members() const
{
	return _members;
}

const std::vector<const Client*>& Channel::get_connected() const
{
	return _connected;
}

const std::string&  Channel::get_password() const
{
	return _password;
}

const std::string&  Channel::get_topic() const
{
	return _topic;
}

bool          Channel::is_invite_only() const
{
	return _invite_only;
}

bool          Channel::is_topic_restricted() const
{
	return _topic_restriction;
}

bool          Channel::is_password_activation() const
{
	return _password_activation;
}

void          Channel::set_invite_only(bool invite_only)
{
	_invite_only = invite_only;
}

void          Channel::set_topic_restriction(bool topic_restriction)
{
	_topic_restriction = topic_restriction;
}

void          Channel::set_password_activation(bool password_activation)
{
	_password_activation = password_activation;
}

void          Channel::set_password(const std::string& password)
{
	_password = password;
}

void          Channel::set_topic(const std::string& topic)
{
	_topic = topic;
	INFO("channel '" + _name + "' topic set to '" + _topic + "'");
}

void          Channel::add_user(const Client* user)
{
	if (std::find(_members.begin(), _members.end(), user) == _members.end())
		_members.push_back(user);
	else
		WARNING("User already in channel");
}

void          Channel::remove_user(const Client* user)
{
	std::vector<const Client*>::iterator it = std::find(_members.begin(), _members.end(), user);
	if (it != _members.end())
		_members.erase(it);
	else
		WARNING("User not in channel");
}

void          Channel::add_admin(const Client* user)
{
	if (std::find(_admins.begin(), _admins.end(), user) == _admins.end())
		_admins.push_back(user);
	else
		WARNING("User already administrator of channel");
}

void          Channel::remove_admin(const Client* user)
{
	std::vector<const Client*>::iterator it = std::find(_admins.begin(), _admins.end(), user);
	if (it != _admins.end())
		_admins.erase(it);
	else
		WARNING("User not administrator of channel");
}

bool		  Channel::is_admin(const Client* user) const
{
	return std::find(_admins.begin(), _admins.end(), user) != _admins.end();
}

void          Channel::send_message(const Client* user, std::string message)
{
	std::vector<const Client*>::iterator it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if (*it != user)
			(*it)->send(message);
	}
}

void 		Channel::send_all(std::string message)
{
	send_message(NULL, message);
}
