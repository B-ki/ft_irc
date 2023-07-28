/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:08:59 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 19:35:27 by rmorel           ###   ########.fr       */
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
		return reply(ERR_NOTREGISTERED(), 452);
	if (_client->get_user() != "*")
		return reply(ERR_ALREADYREGISTERED(), 462);
	if (_message.get_parameters().empty() 
			|| _message.get_parameters()[0].empty())
		return reply(ERR_NEEDMOREPARAMS("USER"), 461);
	std::string username = _message.get_parameters()[0];
	if (!is_valid_username(username))
		return reply(ERR_ERRONEUSNICKNAME(username), 432);
	_client->set_user(username);
	if (_client->has_given_one_name()) {
		_client->set_authenticated(true);
		welcome();
		DEBUG("Welcome message ! Awesome !");
	}
	else {
		_client->set_name_given(true);
		DEBUG("Nick name given, need user now !");
	}
	return 0;
}
