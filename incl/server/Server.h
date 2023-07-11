/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:39 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/11 17:53:29 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <poll.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include "error.h"
# include <vector>
# include <map>
# include "Client.h"
# include <iomanip>


# define DEFAULT_PORT "6667"
# define DEFAULT_PASSWORD "password"
# define MAX_CONNEXIONS 10
# define BUFFER_SIZE 8

class	Server {
	public:
		// -- Constructors --
		Server();
		Server(std::string port, std::string password);
		Server(const Server& server);
		Server&	operator=(const Server& server);

		// -- Destructor --
		~Server();

		// -- Public Functions --
		int	start();
		int	stop();
		int loop();
		int addClient(Client* client);
		int deleteClient(struct pollfd* ptr);
		void printClient();

		// --- Public attributes ---
		bool				_started;

	private:
		// -- Private attributes --
		int						_sockfd;
		std::string				_port;
		std::string				_password;
		std::string				_ip_version;
		struct addrinfo			_hints;
		struct addrinfo*		_servinfo;
		std::vector<pollfd> 	_client_pfd_list;
		std::map<int, Client*> 	_client_list;
		char 					_buffer[BUFFER_SIZE];
};

#endif
