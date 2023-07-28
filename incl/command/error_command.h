/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:20:37 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 17:15:39 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_COMMAND_H
#define ERROR_COMMAND_H 

# include <string>

	std::string ERR_NOSUCHNICK(std::string nick);
	std::string ERR_NOSUCHSERVER(std::string server);
	std::string ERR_NOSUCHCHANNEL(std::string channel);
	std::string ERR_CANNOTSENDTOCHAN(std::string channel);
	std::string ERR_TOOMANYCHANNELS();
	std::string ERR_TOOMANYTARGETS();
	std::string ERR_NORECIPIENT();
	std::string ERR_NOTEXTTOSEND();
	std::string ERR_NOTOPLEVEL();
	std::string ERR_WILDTOPLEVEL();
	std::string ERR_NONICKNAMEGIVEN();
	std::string ERR_ERRONEUSNICKNAME(std::string nick);
	std::string ERR_NICKNAMEINUSE(std::string nick);
	std::string ERR_NICKCOLLISION(std::string nick);
	std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel);
	std::string ERR_NOTONCHANNEL(std::string channel);
	std::string ERR_USERONCHANNEL(std::string nick, std::string channel);
	std::string ERR_NOTREGISTERED();
	std::string ERR_NEEDMOREPARAMS(std::string command);
	std::string ERR_ALREADYREGISTERED();
	std::string ERR_PASSWDMISMATCH();
	std::string ERR_CHANNELISFULL(std::string channel);
	std::string ERR_INVITEONLYCHAN(std::string channel);
	std::string ERR_BANNEDFROMCHAN(std::string channel);
	std::string ERR_BADCHANNELKEY(std::string channel);
	std::string ERR_BADCHANMASK(std::string mask);
	std::string ERR_CHANOPRIVSNEEDED(std::string channel);

#endif
