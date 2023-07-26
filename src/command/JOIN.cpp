#include "command/Command.h"

int Command::execute_JOIN() {
	std::string channel_name = _message.get_parameters()[0];
	Channel* channel = _server->get_channel(channel_name);
	if (channel == NULL) {
		channel = new Channel(channel_name);
		_server->add_channel(channel);
	}
	if (channel->add_client(_client) == -1)
		return reply(ERR_NICKNAMEINUSE(_client->get_nick()), 433);
	return reply(RPL_TOPIC(channel->get_topic()), 332);
}