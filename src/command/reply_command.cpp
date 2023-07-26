/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply_command.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:35:40 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 19:28:28 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "command/reply_command.h"

std::string RPL_AWAY(std::string nick) { return nick + " :User is away"; }
std::string RPL_TOPIC(std::string channel, std::string topic) { return channel + " :" + topic; }
std::string RPL_NOTOPIC(std::string channel) { return channel + " :No topic is set"; }
std::string RPL_TOPICWHOTIME(std::string channel, std::string nick, std::string timestamp) { return channel + " :" + nick + " " + timestamp; }
std::string RPL_INVITING(std::string nick, std::string channel) { return nick + " " + channel + " :You have been invited by "; }
std::string RPL_NAMREPLY(std::string channel, std::string nicks) { return "=" + channel + " :" + nicks; }
std::string RPL_ENDOFNAMES(std::string channel) { return channel + " :End of NAMES list"; }