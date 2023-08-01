/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:37:43 by rmorel            #+#    #+#             */
/*   Updated: 2023/08/01 21:39:53 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Mode.hpp"
#include "command/error_command.h"
#include "command/reply_command.h"

Mode::Mode(std::string modestring, Channel* target, Server* server,
		Client* client) : _target(target), _modestring(modestring),
	_arg(), _end_of_args(), _operand(false), _t_is_set(false), _i_is_set(false),
	_l_is_set(false), _k_is_set(false), _o_is_set(false), _modestring_reply(),
	_args_reply(), _server(server), _client(client)
{
}

Mode::~Mode() {}

bool 	Mode::t_is_set() const { return _t_is_set; };
bool 	Mode::i_is_set() const { return _i_is_set; };
bool 	Mode::l_is_set() const { return _l_is_set; };
bool 	Mode::k_is_set() const { return _k_is_set; };
bool 	Mode::o_is_set() const { return _o_is_set; };

void 	Mode::add_to_modestring_reply(const std::string& mode)
{
	_modestring_reply += mode;
}

void 	Mode::add_to_args_reply(const std::string& arg)
{
	_args_reply.push_back(arg);
}

bool 	Mode::no_more_args() const
{
	return _arg == _end_of_args;
}

const std::string& 		Mode::get_target_name()
{
	return _target->get_name();
}

std::string Mode::MODE_reply()
{
	std::string reply;
	reply += "MODE " + get_target_name() + " " + _modestring_reply;
	for (std::vector<std::string>::const_iterator it = _args_reply.begin();
			it != _args_reply.end(); it++)
	{
		reply += " " + *it;
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
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-'
				&& *it != '$' && '@' && *it != '#')
			return false;
	}
	return true;
}

static bool is_valid_modestring(const std::string& modestring)
{
	if (modestring.empty() || (modestring[0] != '+' && modestring[0] != '-'))
		return false;
	return true;
}

void 	Mode::set_arg(std::vector<std::string>::const_iterator arg)
{
	_arg = arg;
	_arg += 2;
}

void 	Mode::set_end_of_arg(std::vector<std::string>::const_iterator end)
{
	_end_of_args = end;
}

int Mode::reply(std::string message, int code)
{
	if (_client == NULL)
		return -1;
	return _client->reply(message, code);
}

void Mode::protected_topic_mode()
{
	if (_t_is_set == false) {
		_operand ? add_to_modestring_reply("+t") : add_to_modestring_reply("-t");
		_t_is_set = true;
		_target->set_topic_restriction(_operand);
	}
}

void Mode::invite_only_channel_mode()
{
	if (_i_is_set == false) {
		_operand ? add_to_modestring_reply("+i") : add_to_modestring_reply("-i");
		_i_is_set = true;
		_target->set_invite_only(_operand);
	}
}

void Mode::client_limit_mode()
{
	if (_l_is_set == false)
	{
		if (_operand == true && no_more_args()
				&& std::atoi((*_arg).c_str())) {
			_target->set_max_users(std::atoi((*_arg).c_str()));
			add_to_modestring_reply("+l");
			add_to_args_reply(*_arg);
		}
		else {
			_target->set_max_users(0);
			add_to_modestring_reply("-l");
		}
	}
	_arg++;
}

void Mode::key_channel_mode()
{
	if (_k_is_set == false) // ie no password set yet
	{
		_k_is_set = true;
		if (_operand == true && no_more_args()) {
			if (is_valid_password(*_arg)) {
				_target->set_password_activation(true);
				_target->set_password(*_arg);
				add_to_modestring_reply("+k");
				add_to_args_reply(*_arg);
			}
			else
				reply(ERR_INVALIDKEY(get_target_name()), 525);
		}
		else { 
			add_to_modestring_reply("-k");
			_target->set_password_activation(false);
		}
	}
	_arg++;
}

void Mode::oper_user_mode()
{
	if (_o_is_set == false && no_more_args()) {
		_o_is_set = true;
		Client* client = _server->get_client(*_arg);
		if (!client)
			reply(ERR_NOSUCHNICK(*_arg), 401);
		else if (!_target->is_in_channel(client))
			reply(ERR_USERNOTINCHANNEL(*_arg, get_target_name()), 441);
		else if (_operand == true) {
			_target->add_admin(client);
			add_to_modestring_reply("+o");
			add_to_args_reply(*_arg);
		}
		else {
			_target->remove_admin(client);
			add_to_modestring_reply("-o");
			add_to_args_reply(*_arg);
		}
	}
}

int Mode::execute()
{
	if (!is_valid_modestring(_modestring)) {
		WARNING("MODE - Invalid modestring : " << _modestring);
		return -1;
	}
	if (!_target->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(get_target_name()), 482);
	for (std::string::const_iterator it = _modestring.begin(); 
			it != _modestring.end(); it++)
	{
		if (*it == '+')
			_operand = true;
		else if (*it == '-')
			_operand = false;
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
	if (!_modestring.empty())
		_client->send_to(*_client, MODE_reply());
	return 0;
}
