#ifndef REPLY_COMMAND_H
#define REPLY_COMMAND_H 

# include <string>

	std::string RPL_WELCOME();
	std::string RPL_AWAY(const std::string& nick);
	std::string RPL_TOPIC(const std::string& channel, const std::string& topic);
	std::string RPL_NOTOPIC(const std::string& channel);
	std::string RPL_TOPICWHOTIME(const std::string& channel, const std::string& nick, const std::string& timestamp);
	std::string RPL_INVITING(const std::string& nick, const std::string& channel);
	std::string RPL_NAMREPLY(const std::string& channel, const std::string& nicks);
	std::string RPL_ENDOFNAMES(const std::string& channel);

	std::string CMD_JOIN(const std::string& channel);
	std::string CMD_PART(const std::string& channel, const std::string& reason);
	std::string CMD_QUIT(const std::string& reason);
	std::string CMD_KICK(const std::string& channel, const std::string& nick, const std::string& reason);
	std::string CMD_INVITE(const std::string& nick, const std::string& channel);
	std::string CMD_TOPIC(const std::string& channel, const std::string& topic);
	std::string CMD_PRIVMSG(const std::string& channel, const std::string& message);
	std::string CMD_NOTICE(const std::string& channel, const std::string& message);
	std::string CMD_NICK(const std::string& nick);

#endif 
