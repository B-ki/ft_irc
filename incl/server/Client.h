/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:09 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/10 19:06:55 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H 

# include <sys/socket.h>
# include <string.h>
# include <netinet/in.h>
# include <netdb.h>

class Client
{
	public:
		// -- Constructors --
		Client();
		Client(int fd);
		Client(Client& other);
		Client& operator=(const Client& other);

		// -- Destructors --
		~Client();

		// -- Getter --
		int getFd() const;
		void setFd(int fd);
		sockaddr_storage* getStorageAddr();
		socklen_t* getAddrLen();
		char const* getIP() const;
		void setIPAddr();

	private:
		// -- Private attributes --
		int _fd;
		sockaddr_storage _sock_addr;
		char _ip[NI_MAXHOST];
		socklen_t _addrlen;

		// -- Private Functions
};

#endif 
