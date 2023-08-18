#include "command/Command.h"
#include "command/reply_command.h"
#include "constant.h"

Command::Command() : _server(), _client(), _message() {}

Command::~Command() {}

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
	reply(RPL_YOURHOST(_server->get_name(), _server->get_version()), 002);
	reply(RPL_CREATED(_server->get_date_time()), 003);
	reply(RPL_MYINFO(_server->get_name(), _server->get_version(), _server->get_user_modes(), _server->get_channel_modes()), 004);
	reply(RPL_ISUPPORT("CHANMODES=" + _server->get_channel_modes() + " CHANTYPES=#" + " MODES=10"), 005);
	reply(RPL_MOTDSTART(_server->get_name()), 375);
	std::string line;
	std::ifstream infile("assets/logo.txt");
	if (_server->is_sending_welcome_msg()) {
		while (std::getline(infile, line))
			reply(RPL_MOTD(line), 372);
	}
	reply(RPL_MOTD("Nothing important for now ;("), 372);
	reply(RPL_ENDOFMOTD(), 376);
	return 1;
}

int Command::execute_command()
{
	cmd_type cmd = _message.get_cmd();
	std::cout << "Client " << _client->get_nick() << " sent : [" 
		<< _message.get_raw() << "]" << std::endl;
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
		case PART: return execute_PART();
		case KICK: return execute_KICK();
		case INVITE: return execute_INVITE();
		case TOPIC: return execute_TOPIC();
		case PRIVMSG: return execute_PRIVMSG();
		case NOTICE: return execute_NOTICE();
		case MODE: return execute_MODE();
		default: return -1;
	}
}
