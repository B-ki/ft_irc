/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:12:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/27 00:18:43 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/Message.h"
#include "constant.h"
#include "error.h"
#include <exception>
#include <string>
#include <utility>

Message::Message(void) : _raw(), _tags(), _prefix(), _cmd(UNKNOWN), 
	_parameters()
{
}

Message::Message(std::string str_to_parse) : _raw(), _tags(), _prefix(), 
	_cmd(UNKNOWN), _parameters()
{	
	parse_message(str_to_parse);
	print_message();
}

Message::~Message(void) 
{
	this->clear();
}

/*
Message::Message(Message const & src) : _raw(src._raw), _tags(src._tags), 
	_prefix(src._prefix), _cmd(src._cmd), _parameters(src._parameters)
{	
}

Message & Message::operator=(Message const & rhs)
{
	if (this != &rhs)
	{
		this->_raw = rhs._raw;
		this->_tags = rhs._tags;
		this->_prefix = rhs._prefix;
		this->_cmd = rhs._cmd;
		this->_parameters = rhs._parameters;
	}
	return *this;
}
*/
		
std::string Message::get_raw(void) const
{
	return this->_raw;
}

std::map<std::string, std::string> Message::get_tags(void) const
{
	return this->_tags;
}

std::string Message::get_prefix(void) const
{
	return this->_prefix;
}

cmd_type Message::get_cmd(void) const
{
	return this->_cmd;
}

std::vector<std::string> Message::get_parameters(void) const
{
	return this->_parameters;
}

int Message::add_raw(std::string raw)
{
	this->_raw = raw;
	return PARSING_SUCCESS;
}

int Message::add_tag(std::string key, std::string value)
{
	try {
		this->_tags.insert(std::make_pair(key, value));
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}

int Message::add_prefix(std::string prefix)
{
	this->_prefix = prefix;
	return PARSING_SUCCESS;
}

int Message::add_cmd(std::string cmd_str)
{
	const std::string commands[14] = {"UNKOWN", "CAP", "PASS", "NICK", "USER", 
		"JOIN", "PART", "PRIVMSG", "QUIT", "KICK", "INVITE", "NOTICE", "TOPIC", 
		"MODE"};
	for (int i = 0; i < 14; i++)
	{
		if (commands[i] == cmd_str)
		{
			this->_cmd = static_cast<cmd_type>(i);
			return PARSING_SUCCESS;
		}
	}
	ERROR("Unknown command");
	return PARSING_GRAMMAR_ERROR;
}

int Message::add_parameter(std::string parameter)
{
	try {
		this->_parameters.push_back(parameter);
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}

void Message::print_message(void)
{
	std::cout << "---------------" << std::endl;
	std::cout << "-- MESSAGE --" << std::endl;
	std::cout << "Raw : [" << this->_raw << "]" << std::endl;
	std::cout << "Tags :"  << std::endl;
	std::map<std::string, std::string>::iterator it;
	for (it = this->_tags.begin(); it != this->_tags.end(); it++)
		std::cout << "[" << (*it).first << " = " << (*it).second << "]\n";
	std::cout << "Prefix : [" << this->_prefix << "]" << std::endl;
	std::cout << "Cmd : [" << this->_cmd << "]" << std::endl;
	std::cout << "Parameters :"  << std::endl;
	std::vector<std::string>::iterator itv;
	for (itv = this->_parameters.begin(); itv != this->_parameters.end(); itv++)
		std::cout << "[" << *itv << "]" << std::endl;
	std::cout << "---------------" << std::endl;
}

void Message::clear()
{
	this->_raw = "";
	this->_prefix = "";
	this->_tags.clear();
	this->_cmd = UNKNOWN;
	this->_parameters.clear();
}
