#include "command/Command.h"

int Command::execute_TOPIC()
{
	if (_message.get_parameters().empty())
		return reply(ERR_NEEDMOREPARAMS("TOPIC"), 461);
	std::string channel_name = _message.get_parameters()[0];
	Channel* channel = _server->get_channel(channel_name);
	if (channel == NULL)
		return reply(ERR_NOSUCHCHANNEL(channel_name), 403);
	if (!channel->is_in_channel(_client))
		return reply(ERR_NOTONCHANNEL(channel_name), 442);
	if (_message.get_parameters().size() < 2) {
		if (channel->get_topic().empty())
			return reply(RPL_NOTOPIC(channel_name), 331);
		reply(RPL_TOPIC(channel_name, channel->get_topic()), 332);
		// TODO: RPL_TOPICWHOTIME
	} else {
		if (channel->is_topic_restricted() && !channel->is_admin(_client))
			return reply(ERR_CHANOPRIVSNEEDED(channel_name), 482);
		std::string topic = _message.get_parameters()[1];
		channel->set_topic(*_client, topic);
	}
	return 0;
}
