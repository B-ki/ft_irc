/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:39:04 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/27 18:37:43 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command/Command.h"
#include "command/error_command.h"

bool is_valid_nickname(std::string nick)
{
	std::cerr << nick << std::endl;
	for (std::string::iterator it = nick.begin(); it != nick.end(); it++)
	{
		if (!isalpha(*it) && !isdigit(*it) && *it != '[' && *it != ']'
				&& *it != '{' && *it != '}' && *it != '\\' && *it != '|' 
				&& *it != '_' && *it != '-')
			return false;
	}
	return true;
}

bool nick_already_used(std::string nick, std::map<int, Client>& list)
{
	std::map<int, Client>::iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		if ((*it).second.get_nick() == nick)
			return true;
	}
	return false;
}

int Command::execute_NICK()
{
	if (!_client->has_given_pwd())
		return -1;
	if (_message.get_parameters().empty())
		return reply(ERR_NONICKNAMEGIVEN(), 431);
	std::string nick = *_message.get_parameters().begin();
	if (!is_valid_nickname(nick))
		return reply(ERR_ERRONEUSNICKNAME(*_message.get_parameters().begin()), 432);
	if (nick_already_used(nick, _server->get_client_list()))
		return reply(ERR_NICKNAMEINUSE(nick), 433);
	_client->set_nick(nick);
	return 0;
}
