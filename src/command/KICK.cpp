#include "command/Command.h"

int     Command::execute_KICK() {
	if (_message.get_parameters().size() < 2)
		return reply(ERR_NEEDMOREPARAMS(_message.get_command()), 461);
	const std::string& channel_name = _message.get_parameters()[0];
	Channel* channel = _server->get_channel(channel_name);
	if (!channel)
		return reply(ERR_NOSUCHCHANNEL(channel_name), 403);
	if (!channel->is_in_channel(_client))
		return reply(ERR_NOTONCHANNEL(channel_name), 442);
	if (!channel->is_admin(_client))
		return reply(ERR_CHANOPRIVSNEEDED(channel_name), 482);
	const std::vector<std::string>& nicks = utils::split(_message.get_parameters()[1], ",");
	const std::string& reason = _message.get_parameters().size() > 2 ? _message.get_parameters()[2] : _client->get_nick();
	for (size_t i = 0; i < nicks.size(); i++) {
		const Client* target = _server->get_client(nicks[i]);
		if (!target || !channel->is_in_channel(target))
			reply(ERR_USERNOTINCHANNEL(nicks[i], channel_name), 401);
		else
			channel->kick_user(_client, target, reason);
		if (channel->is_empty())
			_server->delete_channel(channel->get_name());
	}
	return 0;
}
