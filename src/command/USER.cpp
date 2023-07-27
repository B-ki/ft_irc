/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:08:59 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/27 18:36:46 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"
#include "command/error_command.h"

bool is_valid_username(std::string user)
{
	for (std::string::iterator it = user.begin(); it != user.end(); it++)
	{
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-')
			return false;
	}
	return true;
}

bool username_already_used(std::string username, std::map<int, Client>& list)
{
	std::map<int, Client>::iterator it = list.begin();
	for (; it != list.end(); it++)
	{
		if ((*it).second.get_nick() == username)
			return true;
	}
	return false;
}

int Command::execute_USER()
{
	if (!_client->has_given_pwd() || _client->get_nick().empty())
		return -1;
	if (_message.get_parameters().empty())
		return reply(ERR_NEEDMOREPARAMS("USER"), 461);
	std::string username = *_message.get_parameters().begin();
	if (!is_valid_username(username))
		return -1;
		//return reply(ERR_ERRONEUSNICKNAME(*_message.get_parameters().begin()), 432);
	if (username_already_used(username, _server->get_client_list()))
		return reply(ERR_NICKNAMEINUSE(username), 433);
	_client->set_user(username);
	welcome();
	return 0;
}
