/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:20:37 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 19:28:20 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "command/error_command.h"

std::string ERR_NOSUCHNICK(std::string nick) { return nick + " :No such nick/channel"; }
std::string ERR_NOSUCHSERVER(std::string server) { return server + " :No such server"; }
std::string ERR_NOSUCHCHANNEL(std::string channel) { return channel + " :No such channel"; }
std::string ERR_CANNOTSENDTOCHAN(std::string channel) { return "Cannot send to channel " + channel; }
std::string ERR_TOOMANYCHANNELS() { return "You have joined too many channels"; }
std::string ERR_TOOMANYTARGETS() { return "Too many targets"; }
std::string ERR_NORECIPIENT() { return " :No recipient given (<command>)"; }
std::string ERR_NOTEXTTOSEND() { return " :No text to send"; }
std::string ERR_NOTOPLEVEL() { return "No top level"; }
std::string ERR_WILDTOPLEVEL() { return "Wild top level"; }
std::string ERR_NONICKNAMEGIVEN() { return " :No nickname given"; }
std::string ERR_ERRONEUSNICKNAME(std::string nick) { return nick + " :Erroneous nickname"; }
std::string ERR_NICKNAMEINUSE(std::string nick) { return nick + " :Nickname is already in use"; }
std::string ERR_NICKCOLLISION(std::string nick) { return nick + " :Nickname collision KILL from"; }
std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel) { return nick + " " + channel + " :They aren't on that channel"; }
std::string ERR_NOTONCHANNEL(std::string channel) { return " :You're not on that channel " + channel; }
std::string ERR_USERONCHANNEL(std::string nick, std::string channel) { return nick + " is already on channel " + channel; }
std::string ERR_NEEDMOREPARAMS(std::string command) { return " :Not enough parameters for command " + command; }
std::string ERR_ALREADYREGISTERED() { return " :You may not reregister"; }
std::string ERR_PASSWDMISMATCH() { return ":Password incorrect"; }
std::string ERR_CHANNELISFULL(std::string channel) { return " :Cannot join channel " + channel + " (+l)"; }
std::string ERR_INVITEONLYCHAN(std::string channel) { return " :Cannot join channel " + channel + " (+i)"; }
std::string ERR_BANNEDFROMCHAN(std::string channel) { return " :Cannot join channel " + channel + " (+b)"; }
std::string ERR_BADCHANNELKEY(std::string channel) { return " :Cannot join channel " + channel + " (+k)"; }
std::string ERR_BADCHANMASK(std::string mask) { return " :Bad Channel Mask " + mask; }
std::string ERR_CHANOPRIVSNEEDED(std::string channel) { return " :You're not channel operator in " + channel; }

