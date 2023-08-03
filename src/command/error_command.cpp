# include "command/error_command.h"

std::string ERR_NOSUCHNICK(const std::string& nick) { return nick + " :No such nick/channel"; }
std::string ERR_NOSUCHCHANNEL(const std::string& channel) { return channel + " :No such channel"; }
std::string ERR_CANNOTSENDTOCHAN(const std::string& channel) { return channel + " :Cannot send to channel"; }
std::string ERR_TOOMANYCHANNELS() { return ":You have joined too many channels"; }
std::string ERR_NORECIPIENT() { return ":No recipient given (<command>)"; }
std::string ERR_NOTEXTTOSEND() { return ":No text to send"; }
std::string ERR_NONICKNAMEGIVEN() { return ":No nickname given"; }
std::string ERR_ERRONEUSNICKNAME(const std::string& nick) { return nick + " :Erroneous nickname"; }
std::string ERR_NICKNAMEINUSE(const std::string& nick) { return nick + " :Nickname is already in use"; }
std::string ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel) { return nick + " " + channel + " :They aren't on that channel"; }
std::string ERR_NOTONCHANNEL(const std::string& channel) { return channel + " :You're not on that channel"; }
std::string ERR_USERONCHANNEL(const std::string& nick, const std::string& channel) { return nick + " " + channel + " :is already on channel"; }
std::string ERR_NOTREGISTERED() { return ":You have not registered"; }
std::string ERR_NEEDMOREPARAMS(const std::string& command) { return command + " :Not enough parameters"; }
std::string ERR_ALREADYREGISTERED() { return ":You may not reregister"; }
std::string ERR_PASSWDMISMATCH() { return ":Password incorrect"; }
std::string ERR_CHANNELISFULL(const std::string& channel) { return channel + " :Cannot join channel (+l)"; }
std::string ERR_UNKNOWNMODE(const std::string& modechar) { return modechar + " :is unknown mode char to me"; }
std::string ERR_INVITEONLYCHAN(const std::string& channel) { return channel + " :Cannot join channel (+i)"; }
std::string ERR_BADCHANNELKEY(const std::string& channel) { return channel + " :Cannot join channel (+k)"; }
std::string ERR_BADCHANMASK(const std::string& channel) { return channel + " :Invalid channel name"; }
std::string ERR_CHANOPRIVSNEEDED(const std::string& channel) { return channel + " :You're not channel operator"; }
std::string ERR_UNKNOWNCOMMAND(const std::string& command) { return command + " :Unknown command"; }
std::string ERR_INVALIDKEY(const std::string& target) { return target + " :Key is not well-formed"; }
std::string ERR_INVALIDMODEPARAM(const std::string& channel, const std::string& mode_string,
								 const std::string& parameter, const std::string& mode,
								 const std::string& token, const std::string& type) {
	std::string res = channel + " " + mode_string + " " + parameter + " :";
	if (type == "INVALID") res += "Invalid " + mode + " mode parameter.";
	else res += "You must specify a parameter for the " + mode + " mode.";
	res += " Syntax: <" + token + ">";
	return res;
}


