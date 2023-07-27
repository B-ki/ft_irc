#include "management/Channel.h"
#include "error.h"
#include "command/reply_command.h"

Channel::Channel()
: _name(), _admins(), _members(), _invite_only(false), _topic_restriction(false), _password_restriction(false), _password(""), _topic(""), _max_users(10)
{
}

Channel::Channel(const Client* user, const std::string& name)
: _name(name), _admins(), _members(), _invite_only(false), _topic_restriction(false), _password_restriction(false), _password(""), _topic(""), _max_users(10)
{
	add_admin(user);
	add_user(user);
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
		_invite_only = other._invite_only;
		_topic_restriction = other._topic_restriction;
		_password_restriction = other._password_restriction;
		_password = other._password;
		_topic = other._topic;
		_max_users = other._max_users;
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

bool          Channel::is_password_restricted() const
{
	return _password_restriction;
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
	_password_restriction = password_activation;
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
	if (find_user(_members, user) == _members.end()) {
		_members.push_back(user);
		send_all(user->get_nick() + " JOIN :" + _name);
		user->reply(RPL_NAMREPLY(_name, get_nicks_list()), 353);
		user->reply(RPL_ENDOFNAMES(_name), 366);
	}
	else {
		WARNING("User already in channel");
	}
}

void          Channel::remove_user(const Client* user)
{
	// TODO send users infos
	std::vector<const Client*>::iterator it = find_user(_members, user);
	if (it != _members.end())
		_members.erase(it);
	else
		WARNING("User not in channel");
}

void          Channel::add_admin(const Client* user)
{
	if (find_user(_admins, user) == _admins.end())
		_admins.push_back(user);
	else
		WARNING("User already administrator of channel");
}

void          Channel::remove_admin(const Client* user)
{
	std::vector<const Client*>::iterator it = find_user(_admins,user);
	if (it != _admins.end())
		_admins.erase(it);
	else
		WARNING("User not administrator of channel");
}

bool		  Channel::is_admin(const Client* user) const
{
	return find_user(_admins, user) != _admins.end();
}

bool          Channel::is_in_channel(const Client* user) const
{
	return find_user(_members, user) != _members.end();
}

void          Channel::send_message(const Client* user, std::string message)
{
	std::vector<const Client*>::iterator it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if (*it != user)
			(*it)->send(message + "\n");
	}
}

void 		Channel::send_all(std::string message)
{
	send_message(NULL, message);
}

bool          Channel::is_full() const
{
	return _members.size() >= _max_users;
}

bool          Channel::is_banned(const Client* user) const
{
	// TODO ban list
	(void)user;
	return false;
}

bool		  Channel::is_invited(const Client* user) const
{
	(void)user;
	if (!_invite_only)
		return true;
	return false;
	// TODO handle invite list
}

bool          Channel::validate_password(const std::string& password) const
{
	return _password == password;
}

std::vector<const Client*>::const_iterator    Channel::find_user(const std::vector<const Client*>& list, const Client* elem) const
{
	std::vector<const Client*>::const_iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		if (*it == elem)
			return it;
	}
	return list.end();
}

std::vector<const Client*>::iterator    Channel::find_user(std::vector<const Client*>& list, const Client* elem)
{
	std::vector<const Client*>::iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		if (*it == elem)
			return it;
	}
	return list.end();
}

std::string Channel::get_nicks_list() const
{
	std::string nicks_list;
	std::vector<const Client*>::const_iterator it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if (is_admin(*it))
			nicks_list += "@";
		nicks_list += (*it)->get_nick();
		if (it + 1 != _members.end())
			nicks_list += " ";
	}
	return nicks_list;
}
