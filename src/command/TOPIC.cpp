#include "command/Command.h"

int     Command::execute_TOPIC() {
	if (_message.get_parameters().empty())
		return reply(ERR_NEEDMOREPARAMS("TOPIC"), 461);
	if (!_server->channel_exists(_message.get_parameters()[0]))
		return reply(ERR_NOSUCHCHANNEL(_message.get_parameters()[0]), 403);
	Channel* channel = _server->get_channel(_message.get_parameters()[0]);
	if (!channel->is_in_channel(_client))
		return reply(ERR_NOTONCHANNEL(_message.get_parameters()[0]), 442);
	if (_message.get_parameters().size() == 1) {
		if (channel->get_topic().empty())
			return reply(RPL_NOTOPIC(channel->get_name()), 331);
		reply(RPL_TOPIC(channel->get_name(), channel->get_topic()), 332);
		reply(RPL_TOPICWHOTIME(channel->get_name(), channel->get_topic_setter_nick(), channel->get_topic_set_time()), 333);
		return 0;
	}
	if (channel->is_topic_restricted() && !channel->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(channel->get_name()), 482);
	channel->set_topic(*_client, _message.get_parameters()[1]);
	return 0;
}
