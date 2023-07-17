/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:20:37 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/17 23:39:50 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H 

# include <string>
# include <sys/socket.h>

# define ERR_NOSUCHNICK " :No such nick/channel"
# define ERR_NOSUCHSERVER " :No such server"
# define ERR_NOSUCHCHANNEL " :No such channel"
# define ERR_CANNOTSENDTOCHAN " :Cannot send to channel"
# define ERR_TOOMANYCHANNELS " :You have joined too many channels"
# define ERR_TOOMANYTARGETS "Too many targets" // COMMANDE BIZARRE A CHECK
# define ERR_NORECIPIENT " :No recipient given (<command>)"
# define ERR_NOTEXTTOSEND " :No test to send"
# define ERR_NOTOPLEVEL "No top level" // COMMANDE BIZARRE A CHECK
# define ERR_WILDTOPLEVEL "Wild top level" // COMMANDE BIZARRE A CHECK
# define ERR_NONICKNAMEGIVEN " :No nickname given"
# define ERR_ERRONEUSNICKNAME " :Erroneus nickname"
# define ERR_NICKNAMEINUSE " :Nickname is already in use"
# define ERR_NICKCOLLISION " :Nickname collision KILL from "
# define ERR_USERNOTINCHANNEL " :They aren't on that channel"
# define ERR_NOTONCHANNEL " :You're not on that channel"
# define ERR_USERONCHANNEL "is already on channel"
# define ERR_NEEDMOREPARAMS " :Not enough parameters"
# define ERR_ALREADYREGISTERED " :You may not reregister"
# define ERR_PASSWDMISMATCH " :Password incorrect"
# define ERR_CHANNELISFULL " :Cannot join channel (+l)" // Pas sur qu'on l'utilise
# define ERR_INVITEONLYCHAN " :Cannot join channel (+i)"
# define ERR_BANNEDFROMCHAN " :Cannot join channel (+b)"
# define ERR_BADCHANNELKEY " :Cannot join channel (+k)"
# define ERR_BADCHANMASK " :Bad Channel Mask"
# define ERR_CHANOPRIVSNEEDED " :You're not channel operator"

#define ERROR_MESSAGES_MAP \
	ERROR_MESSAGE(401, ERR_NOSUCHNICK) \
	ERROR_MESSAGE(402, ERR_NOSUCHSERVER) \
	ERROR_MESSAGE(403, ERR_NOSUCHCHANNEL) \
	ERROR_MESSAGE(404, ERR_CANNOTSENDTOCHAN) \
	ERROR_MESSAGE(405, ERR_TOOMANYCHANNELS) \
	ERROR_MESSAGE(407, ERR_TOOMANYTARGETS) \
	ERROR_MESSAGE(411, ERR_NORECIPIENT) \
	ERROR_MESSAGE(412, ERR_NOTEXTTOSEND) \
	ERROR_MESSAGE(413, ERR_NOTOPLEVEL) \
	ERROR_MESSAGE(414, ERR_WILDTOPLEVEL) \
	ERROR_MESSAGE(431, ERR_NONICKNAMEGIVEN) \
	ERROR_MESSAGE(432, ERR_ERRONEUSNICKNAME) \
	ERROR_MESSAGE(433, ERR_NICKNAMEINUSE) \
	ERROR_MESSAGE(436, ERR_NICKCOLLISION) \
	ERROR_MESSAGE(441, ERR_USERNOTINCHANNEL) \
	ERROR_MESSAGE(442, ERR_NOTONCHANNEL) \
	ERROR_MESSAGE(443, ERR_USERONCHANNEL) \
	ERROR_MESSAGE(461, ERR_NEEDMOREPARAMS) \
	ERROR_MESSAGE(462, ERR_ALREADYREGISTERED) \
	ERROR_MESSAGE(464, ERR_PASSWDMISMATCH) \
	ERROR_MESSAGE(471, ERR_CHANNELISFULL) \
	ERROR_MESSAGE(473, ERR_INVITEONLYCHAN) \
	ERROR_MESSAGE(474, ERR_BANNEDFROMCHAN) \
	ERROR_MESSAGE(475, ERR_BADCHANNELKEY) \
	ERROR_MESSAGE(476, ERR_BADCHANMASK) \
	ERROR_MESSAGE(482, ERR_CHANOPRIVSNEEDED)

std::string 	get_error_message(int err_code);
int 			error_command(int fd, int err_code, std::string& err_param,
					std::string& err_trailing_mess);

#endif 
