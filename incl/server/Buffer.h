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
# include <string>
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
		int get_length() const;

		// -- Public functions --
		int         receive(int fd);
		int         has_message() const;
		std::string extract_message();
		void        clear();

	private:
		char 			_str[BUFFER_SIZE + 1];
		int 	        _length;
};

#endif 
