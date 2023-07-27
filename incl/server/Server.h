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
# include <vector>
# include <unistd.h>
# include <map>
# include <iomanip>
# include "error.h"
# include "color.h"
# include "Client.h"
# include "management/Channel.h"
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
		const std::string&      get_hostname() const;

		// -- Public Functions --
		int		    start();
		int		    stop();
		int 	    loop();
		int 	    create_client();
		void 	    print_clients();
		bool        channel_exists(std::string name);
		int         create_channel(const Client* client, const std::string& name);
		Channel*    get_channel(const std::string& name);


		// --- Public attributes ---
		bool	_started;

	private:
		// -- Private attributes --
		int						        _sockfd;
		int						        _nb_clients;
		std::string				        _port;
		std::string				        _password;
		std::string				        _ip_version;
		struct addrinfo			        _hints;
		struct addrinfo*		        _servinfo;
		pollfd 	                        _client_pfd_list[MAX_CONNEXIONS];
		std::map<int, Client> 	        _client_list;
		char 					        _buffer[BUFFER_SIZE];
		std::string			            _hostname;
		std::map<std::string, Channel>  _channels;

		// -- Private functions --
		int						handle_recv(int fd, int i, int listener);
		void                    remove_fd(int start);
		int 	                delete_client(int id);
};

#endif
