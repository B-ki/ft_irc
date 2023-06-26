/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:12:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/26 18:33:56 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "constant.h"
#include <exception>
#include <utility>

Message::Message(void) : raw(), tags(), prefix(), parameters()
{
	this->cmd = PRIVMSG;
}

Message::Message(std::string)
{	
}

Message::Message(Message const & src) : raw(src.raw), tags(src.tags), prefix(src.prefix),
	cmd(src.cmd), parameters(src.parameters)
{
}

Message::~Message(void) {}

Message & Message::operator=(Message const & rhs)
{
	if (this != &rhs)
	{
		this->raw = rhs.raw;
		this->tags = rhs.tags;
		this->prefix = rhs.prefix;
		this->cmd = rhs.cmd;
		this->parameters = rhs.parameters;
	}
	return *this;
}
		
std::string Message::get_raw(void) const
{
	return this->raw;
}

std::map<std::string, std::string> Message::get_tags(void) const
{
	return this->tags;
}

std::string Message::get_prefix(void) const
{
	return this->prefix;
}

t_cmd_type Message::get_cmd(void) const
{
	return this->cmd;
}

std::vector<std::string> Message::get_parameters(void) const
{
	return this->parameters;
}

t_parse_return Message::add_raw(std::string raw)
{
	try {
		this->raw = raw;
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}

t_parse_return Message::add_tag(std::string key, std::string value)
{
	try {
		this->tags.insert(std::make_pair(key, value));
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}

t_parse_return Message::add_prefix(std::string prefix)
{
	this->prefix = prefix;
	return PARSING_SUCCESS;
}

t_parse_return Message::add_cmd(std::string cmd_str)
{
	const std::string commands[12] = {"pass", "nick", "user", "join", "part", "leave", "privmsg", "quit", "kick", "invite", "topic", "mode"};
	for (int i = 0; i < 12; i++)
	{
		if (commands[i] == cmd_str)
		{
			this->cmd = static_cast<t_cmd_type>(i);
			return PARSING_SUCCESS;
		}
	}
	return PARSING_GRAMMAR_ERROR;
}

t_parse_return Message::add_parameter(std::string parameter)
{
	try {
		this->parameters.push_back(parameter);
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}
