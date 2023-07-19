/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:59:09 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 19:31:34 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_H
# define COMMAND_H

# include "server/Server.h"
# include "command/error_command.h"
# include "command/reply_command.h"

class Command
{
	public:
		// -- Constructors, Destructors && Operator --
		Command(void);
		Command(const Command& src);
		Command(Server* serv, Client* client, std::string raw_message);
		Command& operator=(const Command& rhs);

		// -- Destructor --
		~Command(void);

		// -- Getters & Setters --
		Server* get_server();
		Client* get_client();
		Message& get_message();

		// -- Error & replies --
		int error(std::string err_mess, int err_code);
		int reply(std::string reply_mess, int reply_code);

		// -- Execute --
		int execute_command();

	private:
		Server* _server;
		Client* _client;
		Message _message;

		// -- Commands --
		int PASS();
		int NICK();
		int USER();
		
};

#endif
