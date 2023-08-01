/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:21:22 by rmorel            #+#    #+#             */
/*   Updated: 2023/08/01 16:30:41 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"
#include "command/error_command.h"
#include "command/reply_command.h"
#include "struct.h"

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

/*
static bool is_mode(char c)
{
	if (c == 't' || c == 'o' || c == 'k' || c == 'i' || c == 'l')
		return true;
	return false;
}
*/

static bool is_valid_modestring(const std::string& modestring)
{
	if (modestring.empty() || (modestring[0] != '+' && modestring[0] != '-'))
		return false;
	/*
	for (std::string::const_iterator it = modestring.begin() + 1;
			it != modestring.end(); it++)
	{
		if (*it != '-' && *it != '+')
			return false;
		it++;
		if (it == modestring.end())
			return false;
		while (it != modestring.end() && is_mode(*it))
			it++;
	}
	*/
	return true;
}

int Command::execute_MODE()
{
	if (_message.get_parameters().empty()) {
		WARNING("MODE - No target provided");
		return -1;
	}
	Channel* target = _server->get_channel(_message.get_parameters()[0]);
	if (!target)
		return reply(ERR_NOSUCHCHANNEL(_message.get_parameters()[0]), 403);
	if (_message.get_parameters().size() == 1)
		return reply(RPL_CHANNELMODEIS(target->get_mode_list()), 324); 
	std::string modestring = _message.get_parameters()[1];
	if (!is_valid_modestring(modestring)) {
		WARNING("MODE - Invalid modestring : " << modestring);
		return -1;
	}
	if (!target->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(target->get_name()), 482);
	bool operand;
	ModeReply manager;
	std::vector<std::string>::const_iterator arg = _message.get_parameters().begin();
	arg += 2;
	std::vector<std::string>::const_iterator end_of_args = _message.get_parameters().end();
	for (std::string::const_iterator it = modestring.begin(); 
			it != modestring.end(); it++)
	{
		if (*it == '+')
			operand = true;
		else if (*it == '-')
			operand = false;
		else if (*it == 't' && manager.t_is_set == false) {
			operand ? manager.modestring += "+t" : manager.modestring += "-t";
			manager.t_is_set = true;
			target->set_topic_restriction(operand);
		}
		else if (*it == 'i' && manager.i_is_set == true) {
			operand ? manager.modestring += "+i" : manager.modestring += "-i";
			manager.i_is_set = true;
			target->set_invite_only(operand);
		}
		else if (*it == 'k') {
			if (manager.k_is_set == false) // ie no password set yet
			{
				manager.k_is_set = true;
				if (operand == true && arg != end_of_args) {
					if (is_valid_password(*arg)) {
						target->set_password_activation(true);
						target->set_password(*arg);
						manager.modestring += "+k";
						manager.args.push_back(*arg);
					}
					else
						reply(ERR_INVALIDKEY(target->get_name()), 525);
				}
				else { 
					manager.modestring += "-k";
					target->set_password_activation(false);
				}
			}
			arg++;
		}
		else if (*it == 'l') {
			if (manager.l_is_set == false)
			{
				if (operand == true && arg != end_of_args
						&& std::atoi((*arg).c_str())) {
					target->set_max_users(std::atoi((*arg).c_str()));
					manager.modestring += "+l";
					manager.args.push_back(*arg);
				}
				else {
					target->set_max_users(0);
					manager.modestring += "-l";
				}
			}
			arg++;
		}
		else if (*it == 'o') {
			if (manager.o_is_set == false && arg != end_of_args) {
				manager.o_is_set = true;
				Client* client = _server->get_client(*arg);
				if (!client)
					reply(ERR_NOSUCHNICK(*arg), 401);
				else if (!target->is_in_channel(client))
					reply(ERR_USERNOTINCHANNEL(*arg, target->get_name()), 441);
				else if (operand == true) {
					target->add_admin(client);
					manager.modestring += "+o";
					manager.args.push_back(*arg);
				}
				else {
					target->remove_admin(client);
					manager.modestring += "-o";
					manager.args.push_back(*arg);
				}
			}
		}
		else {
			std::string modechar;
			modechar += *it;
			reply(ERR_UNKNOWNMODE(modechar), 472);
		}
	}
	return 0;
}
