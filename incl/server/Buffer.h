/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:57:07 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/12 19:08:21 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H 

# include <cstring>

# define BUFFER_SIZE 512

class Buffer
{
	public:
		Buffer();
		Buffer(const Buffer& other);
		~Buffer();

		Buffer& operator=(const Buffer& other);

		char* get_buffer();
		int receive(const int fd);

	private:
		char _s[BUFFER_SIZE]; // Pas de raison d'avoir le buffer en privé
};

#endif 
