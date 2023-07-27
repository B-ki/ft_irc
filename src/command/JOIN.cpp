#include "command/Command.h"

//int Command::execute_JOIN() {
//
//	// TODO search for channel
//	// TODO if channel doesn't exist, create it
//	// TODO check channel rights
//	// TODO join channel if possible
//	return 0;
//}

int Command::execute_JOIN() {
	std::string channel_name = _message.get_parameters()[0];
	Channel* channel = _server->get_channel(channel_name);
	if (channel == NULL) {
		_server->create_channel(_client, channel_name);
	} else if (!channel->is_in_channel(_client)){
		if (channel->is_full())
			return reply(ERR_CHANNELISFULL(channel_name), 471);
		if (channel->is_banned(_client))
			return reply(ERR_BANNEDFROMCHAN(channel_name), 474);
		if (channel->is_invited(_client)) {
			return reply(ERR_INVITEONLYCHAN(channel_name), 473);
		}
		if (channel->is_password_restricted()) {
			if (_message.get_parameters().size() < 2)
				return reply(ERR_PASSWDMISMATCH(), 464);
			if (channel->validate_password(_message.get_parameters()[1]))
				return reply(ERR_PASSWDMISMATCH(), 464);
		}
		channel->add_user(_client);
		return reply(RPL_TOPIC(channel_name, channel->get_topic()), 332);
	}
	return 0;
}
