/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MMode.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:19:08 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/13 12:23:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMODE_HPP
#define MMODE_HPP 

# include "Message.h"

class MMode : Message
{
	public:
		MMode();
		
	private:
		bool 						_i;
		bool 						_t;
		bool 						_k;
		bool 						_o;
		std::vector<std::string> 	_user_to_remove;
		std::vector<std::string> 	_user_to_add;
};

#endif 
