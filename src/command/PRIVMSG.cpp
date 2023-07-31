#include "command/Command.h"

int Command::execute_PRIVMSG() {
	if (_message.get_parameters().size() < 2)
		return reply(ERR_NEEDMOREPARAMS("PRIVMSG"), 461);
	const std::vector<std::string> targets = utils::split(_message.get_parameters()[0], ",");
	const std::string& message = _message.get_parameters()[1];
	for (size_t i = 0; i < targets.size(); i++) {
		if (message.empty()) {
			reply(ERR_NOTEXTTOSEND(), 412);
			continue;
		}
		const std::string& target_name = targets[i];
		if (target_name[0] == '#') {
			Channel* channel = _server->get_channel(target_name);
			if (!channel)
				reply(ERR_NOSUCHCHANNEL(target_name), 403);
			else if (!channel->is_in_channel(_client))
				reply(ERR_CANNOTSENDTOCHAN(target_name), 404);
			else
				channel->send_message(_client, CMD_PRIVMSG(target_name, message));
		} else {
			Client* target = _server->get_client(target_name);
			if (!target)
				reply(ERR_NOSUCHNICK(target_name), 401);
			else
				_client->send_to(*target, CMD_PRIVMSG(target_name, message));
		}
	}
	return 0;
}
