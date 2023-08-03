#ifndef ERROR_COMMAND_H
#define ERROR_COMMAND_H 

# include <string>

std::string ERR_NOSUCHNICK(const std::string& nick);
std::string ERR_NOSUCHSERVER(const std::string& server);
std::string ERR_NOSUCHCHANNEL(const std::string& channel);
std::string ERR_CANNOTSENDTOCHAN(const std::string& channel);
std::string ERR_TOOMANYCHANNELS();
std::string ERR_TOOMANYTARGETS();
std::string ERR_NORECIPIENT();
std::string ERR_NOTEXTTOSEND();
std::string ERR_NOTOPLEVEL();
std::string ERR_WILDTOPLEVEL();
std::string ERR_NONICKNAMEGIVEN();
std::string ERR_ERRONEUSNICKNAME(const std::string& nick);
std::string ERR_NICKNAMEINUSE(const std::string& nick);
std::string ERR_NICKCOLLISION(const std::string& nick);
std::string ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel);
std::string ERR_NOTONCHANNEL(const std::string& channel);
std::string ERR_USERONCHANNEL(const std::string& nick, const std::string& channel);
std::string ERR_NOTREGISTERED();
std::string ERR_NEEDMOREPARAMS(const std::string& command);
std::string ERR_ALREADYREGISTERED();
std::string ERR_PASSWDMISMATCH();
std::string ERR_CHANNELISFULL(const std::string& channel);
std::string ERR_UNKNOWNMODE(const std::string& modechar);
std::string ERR_INVITEONLYCHAN(const std::string& channel);
std::string ERR_BANNEDFROMCHAN(const std::string& channel);
std::string ERR_BADCHANNELKEY(const std::string& channel);
std::string ERR_BADCHANMASK(const std::string& mask);
std::string ERR_CHANOPRIVSNEEDED(const std::string& channel);
std::string ERR_UNKNOWNCOMMAND(const std::string& command);
std::string ERR_INVALIDKEY(const std::string& target);
std::string ERR_INVALIDMODEPARAM(const std::string& channel, const std::string& mode_string,
                                 const std::string& parameter, const std::string& mode,
                                 const std::string& token, const std::string& type);

#endif
