/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:09 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 14:32:52 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H 

# include <sys/socket.h>
# include <string.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string>
# include "server/Buffer.h"

class Client
{
	public:
		// -- Constructors --
		Client();
		Client(int fd);
		Client(const Client& other);
		Client& operator=(const Client& other);

		// -- Destructors --
		~Client();

		// -- Getter --
		int get_fd() const;
		sockaddr_storage* get_storage_addr();
		socklen_t* get_addr_len();
		char const* get_IP() const;
		std::string get_nick() const;
		std::string get_user() const;
		std::string get_real_name() const;
		Buffer& get_buffer();
		bool is_authenticated() const;

		// -- Setter --
		void set_fd(int fd);
		void set_IP();
		void set_nick(std::string const new_nick);
		void set_user(std::string const new_user);
		void set_real_name(std::string const new_real_name);
		void set_authenticated(bool const value);

	private:
		// -- Private attributes --
		int 				_fd;
		sockaddr_storage 	_sock_addr;
		char 				_ip[NI_MAXHOST];
		socklen_t 			_addrlen;
		std::string 		_nick;
		std::string 		_user;
		std::string 		_real_name;
		Buffer 				_buffer;
		bool 				_authenticated;

};

#endif 
