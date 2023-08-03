#include "command/ModeParser.hpp"
#include "command/error_command.h"
#include "command/reply_command.h"

ModeParser::ModeParser(const std::string& modestring, Channel* target, Server* server,
		Client* client, const std::vector<std::string>& args) : _target(target),
		_modestring(modestring), _args(args), _index(0), _operand(false), _last_operand(false),
		_t_is_set(false), _i_is_set(false), _l_is_set(false), _k_is_set(false), _o_is_set(false),
		_modestring_reply(), _args_reply(), _server(server), _client(client)
{}

ModeParser::~ModeParser() {}

void 	ModeParser::add_to_modestring_reply(const std::string& mode) {
	if (_modestring_reply.empty() || _operand != _last_operand) {
		_modestring_reply += (_operand ? "+" : "-");
		_last_operand = _operand;
	}
	_modestring_reply += mode;
}

void 	ModeParser::add_to_args_reply(const std::string& arg) { _args_reply.push_back(arg); }

std::string ModeParser::MODE_reply()
{
	std::string reply;
	reply += "MODE " + _target->get_name() + " ";
	if (_args_reply.empty())
		reply += ":";
	reply += _modestring_reply;
	for (std::vector<std::string>::const_iterator it = _args_reply.begin(); it != _args_reply.end(); it++) {
		if (it + 1 == _args_reply.end()) reply += " :" + *it;
		else reply += " " + *it;
	}
	return reply;
}

static bool is_valid_password(const std::string& password)
{
	if (password.empty())
		return false;
	if (password.size() > 24)
		return false;
	for (std::string::const_iterator it = password.begin() + 1;
			it != password.end(); it++) {
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-' && *it != '$' && '@' && *it != '#')
			return false;
	}
	return true;
}

static bool is_valid_modestring(const std::string& modestring)
{
	if (modestring.size() < 2 || (modestring[0] != '+' && modestring[0] != '-'))
		return false;
	return true;
}

int ModeParser::reply(const std::string& message, int code)
{
	if (_client == NULL)
		return -1;
	return _client->reply(message, code);
}

void ModeParser::protected_topic_mode()
{
	if (!_t_is_set && _target->is_topic_restricted() != _operand) {
		add_to_modestring_reply("t");
		_t_is_set = true;
		_target->set_topic_restriction(_operand);
	}
}

void ModeParser::invite_only_channel_mode()
{
	if (!_i_is_set &&  _target->is_invite_only() != _operand) {
		add_to_modestring_reply("i");
		_i_is_set = true;
		_target->set_invite_only(_operand);
	}
}

void ModeParser::client_limit_mode()
{
	if (!_l_is_set) {
		if (_operand) {
			if (_index >= _args.size()) {
				reply(ERR_INVALIDMODEPARAM(_target->get_name(), "l", "*", "limit",
										   "limit", "PARAM"), 696);
			} else if (std::atoi((_args[_index]).c_str()) > 0) {
				int limit = std::atoi((_args[_index]).c_str());
				if (limit != _target->get_max_users()) {
					_target->set_max_users(limit);
					add_to_modestring_reply("l");
					add_to_args_reply(_args[_index]);
				}
			} else {
				reply(ERR_INVALIDMODEPARAM(_target->get_name(), "l", _args[_index],
										   "limit", "limit", "INVALID"), 696);
			}
			_index++;
		} else  if (_target->get_max_users() > 0) {
			_target->set_max_users(0);
			add_to_modestring_reply("l");
		}
	} else if (_operand) _index++;
}

void ModeParser::key_channel_mode()
{
	if (!_k_is_set) {
		_k_is_set = true;
		if (_operand) {
			if (_index >= _args.size()) {
				reply(ERR_INVALIDMODEPARAM(_target->get_name(), "k", "*", "key",
										   "key", "PARAM"), 696);
			} else if (is_valid_password(_args[_index])) {
				_target->set_password_activation(true);
				_target->set_password(_args[_index]);
				add_to_modestring_reply("k");
				add_to_args_reply(_args[_index]);
			} else {
				reply(ERR_INVALIDKEY(_target->get_name()), 525);
			}
			_index++;
		} else if (_target->is_password_restricted()) {
			add_to_modestring_reply("k");
			_target->set_password_activation(false);
		}
	} else if (_operand) _index++;
}

void ModeParser::oper_user_mode()
{
	if (!_o_is_set) {
		if (_index >= _args.size()) {
			reply(ERR_INVALIDMODEPARAM(_target->get_name(), "o", "*", "operator",
									   "operator", "PARAM"), 696);
		} else {
			_o_is_set = true;
			Client* client = _server->get_client(_args[_index]);
			if (!client || !_target->is_in_channel(client))
				reply(ERR_USERNOTINCHANNEL(_args[_index], _target->get_name()), 441);
			else if (_operand && !_target->is_admin(client)) {
				_target->add_admin(client);
				add_to_modestring_reply("o");
				add_to_args_reply(_args[_index]);
			} else if (!_operand && _target->is_admin(client)) {
				_target->remove_admin(client);
				add_to_modestring_reply("o");
				add_to_args_reply(_args[_index]);
			}
		}
	}
	_index++;
}

int ModeParser::execute()
{

	if (!is_valid_modestring(_modestring)) {
		WARNING("MODE - Invalid modestring : " << _modestring);
		return -1;
	}
	if (!_target->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(_target->get_name()), 482);
	_index = 2;
	for (std::string::const_iterator it = _modestring.begin(); it != _modestring.end(); it++) {
		if (*it == '+' || *it == '-')
			_operand = (*it == '+');
		else if (*it == 't')
			protected_topic_mode();
		else if (*it == 'i')
			invite_only_channel_mode();
		else if (*it == 'k')
			key_channel_mode();
		else if (*it == 'l')
			client_limit_mode();
		else if (*it == 'o')
			oper_user_mode();
		else {
			std::string modechar;
			modechar += *it;
			reply(ERR_UNKNOWNMODE(modechar), 472);
		}
	}
	if (!_modestring_reply.empty()) {
		_target->send_all(_client, MODE_reply());
	}
	return 0;
}
