/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:14:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/18 18:09:25 by rmorel           ###   ########.fr       */
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

int Command::error(std::string err_mess, int err_code)
{
	std::string final_message = _client->get_nick() + " " + err_mess;
	if (_client == NULL)
		return -1;
	if (send(_client->get_fd(), final_message.c_str(), sizeof(final_message), 0) == -1)
		ERROR("sending error message");
	return err_code;
}

int Command::reply(std::string reply_mess, int reply_code)
{
	std::string final_message = _client->get_nick() + " " + reply_mess;
	if (_client == NULL)
		return -1;
	if (send(_client->get_fd(), final_message.c_str(), sizeof(final_message), 0) == -1)
		ERROR("sending reply message");
	return reply_code;
}

int Command::PASS(std::string password)
{

	return 0;
}
