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
	std::string RPL_AWAY(std::string nick);
	std::string RPL_TOPIC(std::string channel, std::string topic);
	std::string RPL_NOTOPIC(std::string channel);
	std::string RPL_TOPICWHOTIME(std::string channel, std::string nick, std::string timestamp);
	std::string RPL_INVITING(std::string nick, std::string channel);
	std::string RPL_NAMREPLY(std::string channel, std::string nicks);
	std::string RPL_ENDOFNAMES(std::string channel);

#endif 
