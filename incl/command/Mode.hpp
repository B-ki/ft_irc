/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:38:03 by rmorel            #+#    #+#             */
/*   Updated: 2023/08/01 21:34:45 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MODE_H
# define MODE_H

# include "server/Server.h"

class Mode
{
	public:

		// -- Constructors, Destructors && Operator --

		Mode(std::string modestring, Channel* target, Server* server,
				Client* client);
		~Mode(void);

		// -- Getters --
		bool 					t_is_set() const;
		bool 					i_is_set() const;
		bool 					l_is_set() const;
		bool 					k_is_set() const;
		bool 					o_is_set() const;
		bool 					no_more_args() const;
		const std::string& 		get_target_name();

		// -- Setters --
		
		void 	set_arg(std::vector<std::string>::const_iterator arg);
		void 	set_end_of_arg(std::vector<std::string>::const_iterator end);
		void 	add_to_modestring_reply(const std::string& mode);
		void 	add_to_args_reply(const std::string& arg);

		// -- Execution --

		int 	execute();

		// -- Reply --

		std::string 	MODE_reply();
		int 			reply(std::string message, int code);

	private:
		Channel* 									_target;
		std::string 								_modestring;
		std::vector<std::string>::const_iterator 	_arg;
		std::vector<std::string>::const_iterator 	_end_of_args;;
		bool 										_operand;
		bool 										_t_is_set;
		bool 										_i_is_set;
		bool 										_l_is_set;
		bool 										_k_is_set;
		bool 										_o_is_set;
		std::string 								_modestring_reply;
		std::vector<std::string> 					_args_reply;
		Server* 									_server;
		Client* 									_client;

		// -- Execution --

		void 	invite_only_channel_mode();
		void 	protected_topic_mode();
		void 	client_limit_mode();
		void 	oper_user_mode();
		void 	key_channel_mode();
};

#endif
