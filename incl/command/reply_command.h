#ifndef REPLY_COMMAND_H
#define REPLY_COMMAND_H 

# include <string>

std::string RPL_WELCOME();
std::string RPL_YOURHOST(const std::string& server_name, const std::string& version);
std::string RPL_CREATED(const std::string& date);
std::string RPL_MYINFO(const std::string& server_name, const std::string& version, const std::string& user_modes, const std::string& channel_modes);
std::string RPL_ISUPPORT(const std::string& tokens);
std::string RPL_MOTDSTART(const std::string& server_name);
std::string RPL_MOTD(const std::string& message);
std::string RPL_ENDOFMOTD();
std::string RPL_CHANNELMODEIS(const std::string& channel, const std::string& mode_list);
std::string RPL_AWAY(const std::string& nick);
std::string RPL_TOPIC(const std::string& channel, const std::string& topic);
std::string RPL_NOTOPIC(const std::string& channel);
std::string RPL_TOPICWHOTIME(const std::string& channel, const std::string& nick, const std::string& timestamp);
std::string RPL_INVITING(const std::string& nick, const std::string& channel);
std::string RPL_NAMREPLY(const std::string& channel, const std::string& nicks);
std::string RPL_ENDOFNAMES(const std::string& channel);

std::string CMD_QUIT(const std::string& reason);
std::string CMD_NICK(const std::string& nick);
std::string CMD_JOIN(const std::string& channel);
std::string CMD_PART(const std::string& channel, const std::string& reason);
std::string CMD_KICK(const std::string& channel, const std::string& nick, const std::string& reason);
std::string CMD_INVITE(const std::string& nick, const std::string& channel);
std::string CMD_TOPIC(const std::string& channel, const std::string& topic);
std::string CMD_PRIVMSG(const std::string& channel, const std::string& message);
std::string CMD_NOTICE(const std::string& channel, const std::string& message);

#endif 
