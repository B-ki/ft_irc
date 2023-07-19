/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:57:07 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 11:14:38 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H 

# include <cstring>

# define BUFFER_SIZE 8

class Buffer
{
	public:
		// -- Constructors --
		Buffer();
		Buffer(const Buffer& other);
		Buffer& operator=(const Buffer& other);

		// -- Destructor --
		~Buffer();

		// -- Getter --
		char* 	get_buffer(); // const member ? 
		int 	get_end_message() const;

		int receive(const int fd);

	private:
		char 			_s[BUFFER_SIZE]; // Pas de raison d'avoir le buffer en privé
		unsigned int 	length;
};

#endif 
