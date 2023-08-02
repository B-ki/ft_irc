#include "command/Command.h"

int Command::execute_INVITE() {
	if (_message.get_parameters().size() < 2)
		return reply(ERR_NEEDMOREPARAMS("INVITE"), 461);
	std::string nickname = _message.get_parameters()[0];
	std::string channel_name = _message.get_parameters()[1];
	if (!_server->channel_exists(channel_name))
		return reply(ERR_NOSUCHCHANNEL(channel_name), 403);
	Channel* channel = _server->get_channel(channel_name);
	if (!channel->is_in_channel(_client))
		return reply(ERR_NOTONCHANNEL(channel_name), 442);
	if (!channel->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(channel_name), 482);
	Client* target = _server->get_client(nickname);
	if (!target)
		return reply(ERR_NOSUCHNICK(nickname), 401);
	if (channel->is_in_channel(target))
		return reply(ERR_USERONCHANNEL(nickname, channel_name), 443);
	channel->invite_user(_client, target);
	return 0;
}
