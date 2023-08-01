# include "command/error_command.h"

std::string ERR_NOSUCHNICK(std::string nick) { return nick + " :No such nick/channel"; }
std::string ERR_NOSUCHSERVER(std::string server) { return server + " :No such server"; }
std::string ERR_NOSUCHCHANNEL(std::string channel) { return channel + " :No such channel"; }
std::string ERR_CANNOTSENDTOCHAN(std::string channel) { return channel + " :Cannot send to channel"; }
std::string ERR_TOOMANYCHANNELS() { return ":You have joined too many channels"; }
std::string ERR_TOOMANYTARGETS() { return ":Too many targets"; }
std::string ERR_NORECIPIENT() { return ":No recipient given (<command>)"; }
std::string ERR_NOTEXTTOSEND() { return ":No text to send"; }
std::string ERR_NOTOPLEVEL() { return ":No top level"; }
std::string ERR_WILDTOPLEVEL() { return ":Wild top level"; }
std::string ERR_NONICKNAMEGIVEN() { return ":No nickname given"; }
std::string ERR_ERRONEUSNICKNAME(std::string nick) { return nick + " :Erroneous nickname"; }
std::string ERR_NICKNAMEINUSE(std::string nick) { return nick + " :Nickname is already in use"; }
std::string ERR_NICKCOLLISION(std::string nick) { return nick + " :Nickname collision KILL from"; }
std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel) { return nick + " " + channel + " :They aren't on that channel"; }
std::string ERR_NOTONCHANNEL(std::string channel) { return channel + " :You're not on that channel"; }
std::string ERR_USERONCHANNEL(std::string nick, std::string channel) { return nick + " " + channel + " :is already on channel"; }
std::string ERR_NOTREGISTERED() { return ":You have not registered"; }
std::string ERR_NEEDMOREPARAMS(std::string command) { return command + " :Not enough parameters"; }
std::string ERR_ALREADYREGISTERED() { return ":You may not reregister"; }
std::string ERR_PASSWDMISMATCH() { return ":Password incorrect"; }
std::string ERR_CHANNELISFULL(std::string channel) { return channel + " :Cannot join channel (+l)"; }
std::string ERR_UNKNOWNMODE(std::string modechar) { return modechar + " :is unknown mode char to me"; }
std::string ERR_INVITEONLYCHAN(std::string channel) { return channel + " :Cannot join channel (+i)"; }
std::string ERR_BANNEDFROMCHAN(std::string channel) { return channel + " :Cannot join channel (+b)"; }
std::string ERR_BADCHANNELKEY(std::string channel) { return channel + " :Cannot join channel (+k)"; }
std::string ERR_BADCHANMASK(std::string channel) { return channel + " :Invalid channel name"; }
std::string ERR_CHANOPRIVSNEEDED(std::string channel) { return channel + " :You're not channel operator"; }
std::string ERR_UNKNOWNCOMMAND(std::string command) { return command + " :Unknown command"; }
std::string ERR_INVALIDKEY(std::string target) { return target + " :Key is not well-formed"; }
std::string ERR_INVALIDMOREPARAM(std::string channel, std::string mode_string,
		std::string parameter, std::string description)
{
	return channel + " " + mode_string + " " + parameter + " :" + description;
}


