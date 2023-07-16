/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MMode.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:19:08 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/16 22:35:53 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMODE_HPP
#define MMODE_HPP 

# include "Message.h"

class MMode 
{
	public:
		MMode();
		MMode(const MMode& other);
		MMode(const Message& mess);
		~MMode();
		MMode& operator=(const MMode& other);

		void parse_mode_message(Message mess);
		bool is_modestring(std::string s);
		
	private:
		bool 						_i;
		bool 						_t;
		bool 						_k;
		std::vector<std::string> 	_user_to_remove;
		std::vector<std::string> 	_user_to_add;
};

#endif 
