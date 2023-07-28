/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:41:43 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 19:43:07 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"
#include "command/reply_command.h"

int Command::execute_PASS()
{
	DEBUG("executing PASS with [" << *_message.get_parameters().begin()
			<< "], real pwd = [" << _server->get_password() << "]");
	if (_client->is_authenticated())
		return reply(ERR_ALREADYREGISTERED(), 464);
	if (_message.get_parameters().empty()) 
		return reply(ERR_NEEDMOREPARAMS("PASS"), 461);
	if (_message.get_parameters()[0] != _server->get_password())
		return reply(ERR_PASSWDMISMATCH(), 462);
	_client->set_password_ok(true);
	DEBUG("Password given ! GOOD JOB !");
	return 0;
}
