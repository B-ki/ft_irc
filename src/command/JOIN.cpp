#include "command/Command.h"

static bool is_valid_channel_name(const std::string& channel_name)
{
	if (channel_name.empty())
		return false;
	if (channel_name[0] != '#')
		return false;
	for (std::string::const_iterator it = channel_name.begin(); it != channel_name.end(); it++) {
		if (!isalpha(*it) && !isdigit(*it) && *it != '_' && *it != '-')
			return false;
	}
	return true;
}

void  Command::join_channel(const std::string& channel_name, const std::string& password)
{
	if (!is_valid_channel_name(channel_name)) {
		reply(ERR_BADCHANMASK(channel_name), 476);
	} else {
		Channel* channel = _server->get_channel(channel_name);
		if (channel == NULL) {
			_server->create_channel(_client, channel_name);
		} else if (!channel->is_in_channel(_client)){
			if (channel->is_invited(_client)) {
				channel->add_user(_client);
				reply(RPL_TOPIC(channel_name, channel->get_topic()), 332);
			} else if (channel->is_invite_only())
				reply(ERR_INVITEONLYCHAN(channel_name), 473);
			if (channel->is_full())
				reply(ERR_CHANNELISFULL(channel_name), 471);
			if (channel->is_password_restricted()) {
				if (channel->validate_password(password))
					reply(ERR_PASSWDMISMATCH(), 464);
			}
			channel->add_user(_client);
			reply(RPL_TOPIC(channel_name, channel->get_topic()), 332);
		}
	}
}

static std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos)
			pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

int Command::execute_JOIN()
{
	if (_message.get_parameters().empty())
		return reply(ERR_NEEDMOREPARAMS("JOIN"), 461);
	std::vector<std::string> channels = split(_message.get_parameters()[0], ",");
	std::vector<std::string> passwords;
	if (_message.get_parameters().size() > 1)
		passwords = split(_message.get_parameters()[1], ",");
	for (size_t i = 0; i < channels.size(); i++) {
		if (passwords.size() <= i)
			join_channel(channels[i], "");
		else
			join_channel(channels[i], passwords[i]);
	}
	return 0;
}
