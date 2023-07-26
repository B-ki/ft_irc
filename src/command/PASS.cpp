/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:41:43 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/20 11:32:39 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"

int Command::execute_PASS()
{
	if (_message.get_parameters().empty())
		return error(ERR_NEEDMOREPARAMS("PASS"), 461);
	if (*_message.get_parameters().begin() != _server->get_password())
		return error(ERR_PASSWDMISMATCH(), 462);
	if (_client->is_authenticated())
		return error(ERR_ALREADYREGISTERED(), 464);
	_client->set_authenticated(true);

	return 0;
}
