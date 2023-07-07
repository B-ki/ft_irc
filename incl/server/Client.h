/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:09 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/07 16:35:46 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H 

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
		int getFd();

	private:
		// -- Private attributes --
		int _fd;
};

#endif 
