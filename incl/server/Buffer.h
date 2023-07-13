/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:57:07 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/13 11:24:59 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H 

# include <cstring>

# define BUFFER_SIZE 8

class Buffer
{
	public:
		Buffer();
		Buffer(const Buffer& other);
		~Buffer();

		Buffer& operator=(const Buffer& other);

		char* get_buffer(); // const member ? 
		int receive(const int fd);
		int get_end_message() const;

	private:
		char 			_s[BUFFER_SIZE]; // Pas de raison d'avoir le buffer en privé
		unsigned int 	length;
};

#endif 
