#include "command/Command.h"
#include "command/error_command.h"
#include "command/reply_command.h"
#include "struct.h"
#include "command/ModeParser.hpp"

int Command::execute_MODE()
{
	if (_message.get_parameters().empty()) {
		WARNING("MODE - No target provided");
		return reply(ERR_NEEDMOREPARAMS("MODE"), 461);
	}
	Channel* target = _server->get_channel(_message.get_parameters()[0]);
	if (!target)
		return reply(ERR_NOSUCHCHANNEL(_message.get_parameters()[0]), 403);
	if (_message.get_parameters().size() == 1)
		return reply(RPL_CHANNELMODEIS(target->get_name(), target->get_mode_list()), 324);
	ModeParser mode(_message.get_parameters()[1], target, _server, _client, _message.get_parameters());
	return mode.execute();
}
