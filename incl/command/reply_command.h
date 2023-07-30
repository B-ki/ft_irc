/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply_command.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:40 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/27 17:15:20 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	std::string CMD_PRIVMSG(const std::string& channel, const std::string& message);
	std::string CMD_NOTICE(const std::string& channel, const std::string& message);
	std::string CMD_QUIT();

#endif 
