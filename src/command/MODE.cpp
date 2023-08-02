/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:21:22 by rmorel            #+#    #+#             */
/*   Updated: 2023/08/01 22:29:43 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"
#include "command/error_command.h"
#include "command/reply_command.h"
#include "struct.h"
#include "command/ModeParser.hpp"

ModeReply::ModeReply()
{
	t_is_set = false;
	i_is_set = false;
	l_is_set = false;
	k_is_set = false;
	o_is_set = false;
	modestring = "";
}

static bool is_valid_channel_name(const std::string& channel_name)
{
	if (channel_name.empty())
		return false;
	if (channel_name[0] != '#')
		return false;
	for (std::string::const_iterator it = channel_name.begin() + 1; it != channel_name.end(); it++) {
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-')
			return false;
	}
	return true;
}

int Command::execute_MODE()
{
	if (_message.get_parameters().empty()) {
		WARNING("MODE - No target provided");
		return -1;
	}
	Channel* target = _server->get_channel(_message.get_parameters()[0]);
	if (!is_valid_channel_name(_message.get_parameters()[0]))
		return -1;
	if (!target)
		return reply(ERR_NOSUCHCHANNEL(_message.get_parameters()[0]), 403);
	if (_message.get_parameters().size() == 1)
		return reply(RPL_CHANNELMODEIS(target->get_mode_list()), 324); 
	ModeParser mode(_message.get_parameters()[1], target, _server, _client);
	_message.print_message();
	for (std::vector<std::string>::const_iterator it = _message.get_parameters().begin();
			it != _message.get_parameters().end(); it++)
		std::cout << "[" << *it << "], ";
	std::cout << std::endl;
	mode.set_arg(_message.get_parameters().begin() + 2);
	mode.set_end_of_arg(_message.get_parameters().end());
	return mode.execute();
}
