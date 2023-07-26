/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:59:09 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/24 23:22:30 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_H
# define COMMAND_H

# include "server/Server.h"
# include "constant.h"
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
		int reply(std::string message, int code);

		// -- Execute --
		int execute_command();

	private:
		Server* _server;
		Client* _client;
		Message _message;

		// -- Commands --
		int execute_PASS();
		int execute_NICK();
		int execute_USER();	
};

#endif
