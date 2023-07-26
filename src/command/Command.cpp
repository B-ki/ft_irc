/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:14:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/26 15:18:04 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"

Command::Command() : _server(), _client(), _message()
{
}

Command::~Command()
{
}

Command::Command(Server* serv, Client* client, std::string raw_message)
{
	_server = serv;
	_client = client;
	_message = Message(raw_message);
}

Command::Command(const Command& other)
{
	*this = other;
}

Command& Command::operator=(const Command& other)
{
	if (this != &other) {
		_server = other._server;
		_client = other._client;
		_message = other._message;
	}
	return *this;
}

Server* Command::get_server() { return _server; }
Client* Command::get_client() { return _client; }
Message& Command::get_message() { return _message; }

int Command::reply(std::string message, int code)
{
	std::stringstream final_message;
	final_message << code << " " << _client->get_nick() << " " << message << "\n";
	if (_client == NULL)
		return -1;
	if (_client->send(final_message.str()) != -1)
		ERROR("sending reply message");
	return code;
}

int Command::execute_command()
{
	cmd_type cmd = _message.get_cmd();
	if (cmd != PASS && !_client->is_authenticated())
		return reply(ERR_PASSWDMISMATCH(), 464);
	switch (cmd)
	{
		case PASS: return execute_PASS();
		case NICK: return execute_NICK();
		case USER: return execute_USER();
		default: return -1;
	}
}
