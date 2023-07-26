/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:39 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/26 17:13:16 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <string>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <poll.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include "error.h"
# include "color.h"
# include <vector>
# include <map>
# include "Client.h"
# include <iomanip>
# include "parsing/Message.h"


# define DEFAULT_PORT "6667"
# define DEFAULT_PASSWORD "password"
# define MAX_CONNEXIONS 10

class	Server {
	public:
		// -- Constructors --
		Server();
		Server(std::string port, std::string password);
		Server(const Server& server);
		Server&	operator=(const Server& server);

		// -- Destructor --
		~Server();

		// -- Getter --
		Client* 				get_client(const int fd);
		Client* 				get_client(std::string nick);
		std::string& 			get_password(); 
		std::map<int, Client>& 	get_client_list();

		// -- Public Functions --
		int						start();
		int						stop();
		int 					loop();
		int 					create_client();
		int 					delete_client(struct pollfd* ptr);
		void 					print_client();
		void 					process_buffer();

		// --- Public attributes ---
		bool					_started;

		// --- Command execution ---
		int execute_nick(Message mess);	

	private:
		// -- Private attributes --
		int						_sockfd;
		std::string				_port;
		std::string				_password;
		std::string				_ip_version;
		struct addrinfo			_hints;
		struct addrinfo*		_servinfo;
		std::vector<pollfd> 	_client_pfd_list;
		std::map<int, Client> 	_client_list;
		char 					_buffer[BUFFER_SIZE];
};

#endif
