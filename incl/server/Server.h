/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:36:39 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/06 19:56:48 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <stdlib.h>
# include <unistd.h>
# include "error.h"

# define DEFAULT_PORT "6667"
# define DEFAULT_PASSWORD "password"

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

	private:
		// -- Private attributes --
		bool				_started;
		int					_sockfd;
		std::string			_port;
		std::string			_password;
		std::string			_ip_version;
		struct addrinfo		_hints;
		struct addrinfo*	_servinfo;
};

#endif
