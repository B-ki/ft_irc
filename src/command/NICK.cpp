/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:39:04 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 19:42:55 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command/Command.h"
#include "command/error_command.h"

bool is_valid_nickname(std::string nick)
{
	for (std::string::iterator it = nick.begin(); it != nick.end(); it++)
	{
		if (!isalpha(*it) && !isdigit(*it) && *it != '[' && *it != ']'
				&& *it != '{' && *it != '}' && *it != '\\' && *it != '|' 
				&& *it != '_' && *it != '-')
			return false;
	}
	return true;
}

int Command::execute_NICK()
{
	if (!_client->has_given_password())
		return reply(ERR_NOTREGISTERED(), 451);
	if (_message.get_parameters().empty())
		return reply(ERR_NONICKNAMEGIVEN(), 431);
	std::string nick = _message.get_parameters()[0];
	if (!is_valid_nickname(nick))
		return reply(ERR_ERRONEUSNICKNAME(nick), 432);
	if (_server->nick_already_used(nick))
		return reply(ERR_NICKNAMEINUSE(nick), 433);
	if (_client->get_nick() != "*") {
		_client->set_nick(nick);
		return 0;
	}
	_client->set_nick(nick);
	if (_client->get_user() != "*") {
		_client->set_authenticated(true);
		welcome();
	} else {
		_client->set_name_given(true);
	}
	return 0;
}
