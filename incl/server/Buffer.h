/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:57:07 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/24 21:35:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H 

# include <cstring>
# include "constant.h"

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

		int receive(int fd);

	private:
		char 			_s[BUFFER_SIZE]; // Pas de raison d'avoir le buffer en privé
		unsigned int 	length;
};

#endif 
