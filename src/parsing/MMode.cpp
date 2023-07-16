/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MMode.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:00:24 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/16 22:46:06 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/MMode.h"

MMode::MMode()
{
}

MMode::~MMode()
{
}

MMode::MMode(const MMode& other) 
{
	*this = other;
}

MMode::MMode(const Message& mess) 
{
}

MMode& MMode::operator=(const MMode& other)
{
	if (this != &other) {
		_i = other._i;	
		_k = other._k;	
		_t = other._t;	
		_user_to_add = other._user_to_add;
		_user_to_remove = other._user_to_remove;
	}
	return *this;
}

void MMode::parse_mode_message(Message mess)
{
	if (mess.get_raw().empty())
		return;
	std::vector<std::string> params = mess.get_parameters();
	std::vector<std::string>::iterator it = params.begin();
	std::vector<std::string>::iterator end = params.end();
	//std::vector<std::string>::iterator end2 = mess.get_parameters.end();
	// Can't create iterator directly because get_parameters will be lost
	for(; i != end; i++)
	{

	}
}

bool is_char_modestring(char c)
{
	if (c == '+' || c == '-' || c == 'i' || c == 't' || c == 'k' || c == 'o')
		return true;
	return false;
}

bool MMode::is_modestring(std::string s)
{
	std::string::iterator it = s.begin();
	for (; it != s.end(); it++)
	{
		if (!is_char_modestring(*it))
			return false;
	}
}

bool MMode::char_is_mode(char* s)
{
	if (*s != 'i' || *s != 't' || *s != 'k' || *s != 'o')
		return false;
	return true;
}

