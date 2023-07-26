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
		// -- Public Constructors --
		Channel();
		Channel(const Client* user, const std::string& name);
		Channel(const Channel& other);
		~Channel();
		Channel& operator=(const Channel& other);

		// -- Getters --
		const std::string&                get_name() const;
		const std::vector<const Client*>& get_admins() const;
		const std::vector<const Client*>& get_members() const;
		const std::vector<const Client*>& get_connected() const;
		bool                              is_invite_only() const;
		bool                              is_topic_restricted() const;
		bool                              is_password_activation() const;
		const std::string&                get_password() const;
		const std::string&                get_topic() const;

		// -- Setters
		void    set_invite_only(bool invite_only);
		void    set_topic_restriction(bool topic_restriction);
		void    set_password_activation(bool password_activation);
		void    set_password(const std::string& password);
		void    set_topic(const std::string& topic);

		// -- Public Functions --
		void    add_user(const Client* user);
		void    remove_user(const Client* user);
		void    add_admin(const Client* user);
		void    remove_admin(const Client* user);
		bool    is_admin(const Client* user) const;

		void    send_message(const Client* user, std::string message);
		void    send_all(std::string message);


	private:
		std::string 			    _name;
		std::vector<const Client*>  _admins;
		std::vector<const Client*>  _members;
		std::vector<const Client*>  _connected;
		bool                        _invite_only;
		bool                        _topic_restriction;
		bool                        _password_activation;
		std::string                 _password;
		std::string                 _topic;

};

#endif 
