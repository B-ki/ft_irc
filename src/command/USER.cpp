/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:08:59 by rmorel            #+#    #+#             */
/*   Updated: 2023/08/01 17:22:00 by rmorel           ###   ########.fr       */
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

int Command::execute_USER()
{
	if (!_client->has_given_password())
		return reply(ERR_NOTREGISTERED(), 451);
	if (_client->get_user() != "*")
		return reply(ERR_ALREADYREGISTERED(), 462);
	if (_message.get_parameters().size() < 4)
		return reply(ERR_NEEDMOREPARAMS("USER"), 461);
	std::string username = _message.get_parameters()[0];
	std::string real_name = _message.get_parameters()[3];
	if (!is_valid_username(username))
		return reply(ERR_ERRONEUSNICKNAME(username), 432);
	_client->set_user(username);
	_client->set_real_name(real_name);
	if (_client->get_nick() != "*") {
		_client->set_authenticated(true);
		welcome();
	}
	else {
		_client->set_name_given(true);
	}
	return 0;
}
