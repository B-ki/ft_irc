#include "management/Channel.h"

Channel::Channel(Client* user, const std::string& name)
: _name(name), _admins(), _members(), _invited(), _invite_only(false),
_topic_restriction(true), _password_restriction(false), _max_users(10),
_capacity_restriction(false), _topic_info()
{
	add_admin(user);
	add_user(user);
}

Channel::Channel(const Channel& other) { *this = other; }

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
		_capacity_restriction = other._capacity_restriction;
	}
	return *this;
}

Channel::~Channel() {}

const std::string&  Channel::get_name() const { return _name; }

const std::vector<const Client*>&   Channel::get_admins() const { return _admins; }

const std::vector<const Client*>&   Channel::get_members() const { return _members; }

const std::string&  Channel::get_password() const { return _password; }

const std::string&  Channel::get_topic() const { return _topic; }

bool    Channel::is_invite_only() const { return _invite_only; }

bool    Channel::is_topic_restricted() const { return _topic_restriction; }

bool    Channel::is_password_restricted() const { return _password_restriction; }

void    Channel::set_invite_only(bool invite_only) { _invite_only = invite_only; }

void    Channel::set_topic_restriction(bool topic_restriction) { _topic_restriction = topic_restriction; }

void    Channel::set_password_activation(bool password_activation) { _password_restriction = password_activation; }

void    Channel::set_password(const std::string& password) { _password = password; }

void    Channel::set_topic(const Client& user, const std::string& topic)
{
	if (!is_topic_restricted() || is_admin(&user)) {
		_topic = topic;
		_topic_info = std::make_pair(user.get_nick(), utils::itoa(std::time(NULL)));
		send_all(&user, CMD_TOPIC(_name, _topic));
	}
}

void 	Channel::set_max_users(size_t max_users) { _max_users = max_users; }

void    Channel::add_user(Client* user)
{
	if (find_user(_members, user) == _members.end()) {
		_members.push_back(user);
		user->add_channel(_name);
		send_all(user,  CMD_JOIN(_name));
		if (!_topic.empty()) {
			user->reply(RPL_TOPIC(_name, _topic), 332);
			user->reply(RPL_TOPICWHOTIME(_name, _topic_info.first, _topic_info.second), 333);
		}
		user->reply(RPL_NAMREPLY(_name, get_nicks_list()), 353);
		user->reply(RPL_ENDOFNAMES(_name), 366);
	}
	else {
		WARNING("User already in channel");
	}
}

void    Channel::remove_user(Client* user)
{
	std::vector<const Client*>::iterator it = find_user(_members, user);
	if (it != _members.end()) {
		_members.erase(it);
		user->remove_channel(_name);
	}
	it = find_user(_admins, user);
	if (it != _admins.end())
		_admins.erase(it);
	it = find_user(_invited, user);
	if (it != _invited.end())
		_invited.erase(it);
}

void    Channel::add_admin(const Client* user)
{
	if (find_user(_admins, user) == _admins.end())
		_admins.push_back(user);
	else
		WARNING("User already administrator of channel");
}

void 	Channel::remove_admin(const Client* user)
{
	if (find_user(_admins, user) != _admins.end())
		_admins.erase(find_user(_admins, user));
	else
		WARNING("User is not administrator of channel");
}

bool    Channel::is_admin(const Client* user) const { return find_user(_admins, user) != _admins.end(); }

bool    Channel::is_in_channel(const Client* user) const { return find_user(_members, user) != _members.end(); }

void    Channel::send_message(const Client* user, const std::string& message)
{
	std::vector<const Client*>::iterator it = _members.begin();
	for (; it != _members.end(); it++)
	{
		if (*it != user)
			user->send_to(**it, message);
	}
}

void 	Channel::send_all(const Client* user, const std::string& message)
{
	std::vector<const Client*>::iterator it = _members.begin();
	for (; it != _members.end(); it++)
		user->send_to(**it, message);
}

bool    Channel::is_full() const
{
	if (_max_users == 0)
		return false;
	return _members.size() >= _max_users;
}

bool	Channel::is_invited(const Client* user) const { return find_user(_invited, user) != _invited.end(); }

bool    Channel::validate_password(const std::string& password) const { return _password == password; }

std::vector<const Client*>::const_iterator  Channel::find_user(const std::vector<const Client*>& list, const Client* elem) const
{
	std::vector<const Client*>::const_iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		if (*it == elem)
			return it;
	}
	return list.end();
}

void    Channel::invite_user(const Client *issuer, const Client *target) {
	if (find_user(_invited, target) == _invited.end()) {
		_invited.push_back(target);
		issuer->reply(RPL_INVITING(target->get_nick(), _name), 341);
		issuer->send_to(*target, CMD_INVITE(target->get_nick(), _name));
	}
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

void    Channel::part_user(Client *user, const std::string &reason) {
	std::vector<const Client*>::iterator it = find_user(_members, user);
	if (it != _members.end()) {
		send_all(user, CMD_PART(_name, reason));
		remove_user(user);
	}
}

void    Channel::kick_user(Client *user, Client* target, const std::string &reason) {
	std::vector<const Client*>::iterator it = find_user(_members, target);
	if (it != _members.end()) {
		send_all(user, CMD_KICK(_name, target->get_nick(), reason));
		remove_user(target);
	}
}

void    Channel::quit_user(Client *user, const std::string &reason) {
	std::vector<const Client*>::iterator it = find_user(_members, user);
	if (it != _members.end()) {
		send_message(user, CMD_QUIT(reason));
		remove_user(user);
	}
}

bool    Channel::is_empty() const { return _members.empty(); }

std::string Channel::get_mode_list() const
{
	std::string mode_list = _name + " +";
	std::vector<std::string> args;
	
	if (_topic_restriction)
		mode_list += "t";
	if (_invite_only)
		mode_list += "i";
	if (_capacity_restriction) {
		mode_list += "l";
		args.push_back(utils::itoa(_max_users));
	}
	if (_password_restriction) {
		mode_list += "k";
		args.push_back(_password);
	}
	if (args.empty())
		return mode_list;
	for (std::vector<std::string>::const_iterator it = args.begin();
			it != args.end(); it++)
		mode_list += " " + *it;
	return mode_list;
}

const std::string&  Channel::get_topic_setter_nick() const { return _topic_info.first; }

const std::string&  Channel::get_topic_set_time() const { return _topic_info.second; }
