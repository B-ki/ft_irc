/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:40:47 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/13 11:49:20 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP 

# include "server/Client.h"
# include <vector>

class Channel
{
	public:
		Channel();
		Channel(const Channel& other);
		~Channel();
		Channel& operator=(const Channel& other);

		// Func send message to everyone in channel
		// Func to add member
		// Func to delete member
		// Getters
		// Setters

	private:
		std::vector<Client*> 	_admins;
		std::vector<Client*> 	_members;
		std::vector<Client*> 	_connected;
		bool 					_invite_only;
		bool 					_topic_restriction;
		bool 					_password_activation;
		std::string 			_password;
		std::string 			_topic;

};

#endif 
