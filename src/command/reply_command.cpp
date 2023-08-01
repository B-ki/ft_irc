#include "command/reply_command.h"

std::string RPL_WELCOME() { return ":Welcome to the IRC Network"; }
std::string RPL_AWAY(const std::string& nick) { return nick + " :User is away"; }
std::string RPL_TOPIC(const std::string& channel, const std::string& topic) { return channel + " :" + topic; }
std::string RPL_NOTOPIC(const std::string& channel) { return channel + " :No topic is set"; }
std::string RPL_TOPICWHOTIME(const std::string& channel, const std::string& nick, const std::string& timestamp) { return channel + " :" + nick + " " + timestamp; }
std::string RPL_INVITING(const std::string& nick, const std::string& channel) { return nick + " " + channel; }
std::string RPL_NAMREPLY(const std::string& channel, const std::string& nicks) { return "= " + channel + " :" + nicks; }
std::string RPL_ENDOFNAMES(const std::string& channel) { return channel + " :End of /NAMES list"; }

std::string CMD_JOIN(const std::string& channel) { return "JOIN :" + channel; }
std::string CMD_PART(const std::string& channel, const std::string& reason) {
	if (reason.empty())
		return "PART :" + channel;
	return "PART " + channel + " :" + reason;
}
std::string CMD_QUIT(const std::string& reason) { return "QUIT :" + reason; }
std::string CMD_KICK(const std::string& channel, const std::string& nick, const std::string& reason) { return "KICK " + channel + " " + nick + " :" + reason; }
std::string CMD_INVITE(const std::string& nick, const std::string& channel) { return "INVITE " + nick + " " + channel; }
std::string CMD_TOPIC(const std::string& channel, const std::string& topic) { return "TOPIC " + channel + " :" + topic; }
std::string CMD_PRIVMSG(const std::string& channel, const std::string& message) { return "PRIVMSG " + channel + " :" + message; }
std::string CMD_NOTICE(const std::string& channel, const std::string& message) { return "NOTICE " + channel + " :" + message; }
std::string CMD_NICK(const std::string& nick) { return "NICK :" + nick; }
