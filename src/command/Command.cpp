/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:14:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 19:44:38 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/Command.h"
#include "command/reply_command.h"
#include "constant.h"

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
	if (_client == NULL)
		return -1;
	return _client->reply(message, code);
}

int Command::welcome()
{
	reply(RPL_WELCOME(), 001);
	return 1;
}

int Command::execute_command()
{
	cmd_type cmd = _message.get_cmd();
	if (cmd == UNKNOWN)
		return reply(ERR_UNKNOWNCOMMAND(_message.get_command()), 421);
	if (cmd != CAP && cmd != PASS && cmd != NICK && cmd != USER
			&& !_client->is_authenticated()) {
		ERROR("Trying command without being authenticated");
		return reply(ERR_NOTREGISTERED(), 451);
	}
	switch (cmd)
	{
		case CAP: return 0;
		case PASS: return execute_PASS();
		case NICK: return execute_NICK();
		case USER: return execute_USER();
		case JOIN: return execute_JOIN();
		default: return -1;
	}
}
