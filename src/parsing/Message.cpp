/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:12:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/06 15:07:06 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "constant.h"
#include "error.h"
#include <exception>
#include <string>
#include <utility>

Message::Message(void) : _raw(), _tags(), _prefix(), _nick(),
	_user(), _host(), _parameters()
{
	this->_cmd = NOTHING;
}

Message::Message(std::string)
{	
}

Message::Message(Message const & src) : _raw(src._raw), _tags(src._tags), 
	_prefix(src._prefix), _nick(src._nick), _user(src._user), _host(src._host),
	_cmd(src._cmd), _parameters(src._parameters)
{
	
}

Message::~Message(void) 
{
	this->clear();
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

/* A voir si on garde, pas forcément besoin de parse le prefix
 si pas de communication server to server
std::string Message::get_nick(void) const
{
	return this->nick;
}

std::string Message::get_user(void) const
{
	return this->user;
}

std::string Message::get_host(void) const
{
	return this->host;
}
*/

t_cmd_type Message::get_cmd(void) const
{
	return this->_cmd;
}

std::vector<std::string> Message::get_parameters(void) const
{
	return this->_parameters;
}

t_parse_return Message::add_raw(std::string raw)
{
	this->_raw = raw;
	return PARSING_SUCCESS;
}

t_parse_return Message::add_tag(std::string key, std::string value)
{
	try {
		this->_tags.insert(std::make_pair(key, value));
	} catch (std::exception &e) {
		return PARSING_EXCEPT_ERROR;
	}
	return PARSING_SUCCESS;
}

t_parse_return Message::add_prefix(std::string prefix)
{
	this->_prefix = prefix;
	return PARSING_SUCCESS;
}

/* Idem, a voir si on garde, pas forcément besoin de parse le prefix
t_parse_return Message::add_nick(std::string nick)
{
	this->nick = nick;
	return PARSING_SUCCESS;
}

t_parse_return Message::add_user(std::string user)
{
	this->user = user;
	return PARSING_SUCCESS;
}

t_parse_return Message::add_host(std::string host)
{
	this->host = host;
	return PARSING_SUCCESS;
}*/

t_parse_return Message::add_cmd(std::string cmd_str)
{
	const std::string commands[12] = {"PASS", "NICK", "USER", "JOIN", "PART", "LEAVE", "PRIVMSG", "QUIT", "KICK", "INVITE", "TOPIC", "MODE"};
	for (int i = 0; i < 12; i++)
	{
		if (commands[i] == cmd_str)
		{
			this->_cmd = static_cast<t_cmd_type>(i);
			return PARSING_SUCCESS;
		}
	}
	return PARSING_GRAMMAR_ERROR;
}

t_parse_return Message::add_parameter(std::string parameter)
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
	this->_nick = "";
	this->_user = "";
	this->_host = "";
	this->_cmd = NOTHING;
	this->_parameters.clear();
}

std::pair<std::string, std::string> get_key_value_tag(std::string tag)
{
	int start_index = 0;
	int end_index = 0;
	std::string key;
	std::string value;
	int i = 0;

	int nb_equal_char = std::count(tag.begin(), tag.end(), '=');
	if (nb_equal_char > 1)
		throw std::exception();

	if (nb_equal_char == 0)
		return std::make_pair(tag, "");

	while (tag[i] && tag[i] != '=')
		i++;

	end_index = i;
	key.append(tag, start_index, end_index - start_index);
	start_index = i + 1;
	value.append(tag, start_index, tag.size());
	return (std::make_pair(key, value));
}

t_parse_return Message::parse_tags(std::string all_tags)
{
	all_tags.erase(0, 1);
	int start_index = 0;
	int end_index = 0;
	std::pair<std::string, std::string> tag;

	for (std::string::size_type i = 0; i < all_tags.size(); i++)
	{
		if (all_tags[i] == ';')
		{
			end_index = i;
			std::string temp;
			temp.append(all_tags, start_index, end_index - start_index);
			while (all_tags[i] && all_tags[i++] == ';')
				end_index++;
			try {
				tag = get_key_value_tag(temp);
			} catch (std::exception &e) {
				return (PARSING_EXCEPT_ERROR);
			}
			this->add_tag(tag.first, tag.second);
			start_index = end_index + 1;
		}
	}
	return (PARSING_SUCCESS);
}

t_parse_return Message::handle_tags(std::string &str_to_parse, 
		std::string::iterator &position, size_t &space_pos)
{
		space_pos = str_to_parse.find(' ', space_pos);
		std::string tag_str;

		if (space_pos != std::string::npos)
			tag_str = std::string(position, position + space_pos);
		else 
			return (PARSING_GRAMMAR_ERROR);
		t_parse_return ret = this->parse_tags(tag_str);
		if (ret != 0)
			return (ret);
		position += space_pos;
		return (PARSING_SUCCESS);
}

t_parse_return Message::handle_prefix(std::string &str_to_parse,
		std::string::iterator &position, size_t &space_pos)
{
		space_pos = str_to_parse.find(' ', space_pos);
		std::string prefix_str;

		if (space_pos != std::string::npos)
			prefix_str = std::string(position, position + space_pos);
		else 
			return (PARSING_GRAMMAR_ERROR);
		this->add_prefix(prefix_str);
		position += space_pos;
		return (PARSING_SUCCESS);
}

t_parse_return Message::parse_normal_parameters(std::string normal_params)
{
	std::string::size_type space_pos_1 = 0; 
	std::string::size_type space_pos_2 = 0; 

	while (space_pos_2 < normal_params.size())
	{
		space_pos_2 = normal_params.find(" ", space_pos_1);
		if (space_pos_2 == std::string::npos)
			space_pos_2 = normal_params.size();
		if (*(normal_params.begin() + space_pos_1) != ' ' 
				&& space_pos_2 - space_pos_1 > 0)
		{
			if (*(normal_params.begin() + space_pos_1) == ' ')
				space_pos_1++;
			std::string temp = normal_params.substr(space_pos_1, space_pos_2 - space_pos_1);
			if (this->add_parameter(temp) == PARSING_GRAMMAR_ERROR)
				return (PARSING_GRAMMAR_ERROR);
		}
		space_pos_1 = space_pos_2 + 1;
	}
	return (PARSING_SUCCESS);
}

void Message::skip_space(std::string::iterator &position, size_t &space_pos)
{
	// Skip spaces
	while (*(position) == ' ') {
		position++;
		space_pos++;
	}
}

t_parse_return Message::parse_message(std::string str_to_parse)
{
	if (str_to_parse.empty())
		return (PARSING_EMPTY_MESSAGE);
	std::string::iterator position;
	std::string::iterator nextSpace;
	this->add_raw(str_to_parse);
	size_t space_pos = 0;
	position= str_to_parse.begin();

	// Check if tags are presents
	if (*position == '@') {
		t_parse_return ret = handle_tags(str_to_parse, position, space_pos);
		if (ret != PARSING_SUCCESS)
			return (ret);
	}

	skip_space(position, space_pos);

	// Check if prefix are presents
	if (*position == ':') {
		t_parse_return ret = handle_prefix(str_to_parse, position, space_pos);
		if (ret != PARSING_SUCCESS)
			return (ret);
	}

	skip_space(position, space_pos);

	// Check if there is nothing after the command
	space_pos = str_to_parse.find(' ', space_pos);

	if (space_pos == std::string::npos) {
		std::string cmd_str = std::string(position, str_to_parse.end());
		return (this->add_cmd(cmd_str));
	}

	// If something after cmd, we expect some parameters
	// But first we parse the cmd
	std::string cmd_str = std::string(position, str_to_parse.begin() + space_pos);

	if (this->add_cmd(cmd_str) == PARSING_GRAMMAR_ERROR)
		return (PARSING_GRAMMAR_ERROR);

	position += space_pos;

	skip_space(position, space_pos);

	std::string::size_type colon_pos = str_to_parse.find(':', space_pos);

	// if no trailing parameter :
	if (colon_pos == std::string::npos)	{
		std::string all_normal_params(position, str_to_parse.end());
		return (parse_normal_parameters(all_normal_params));
	}

	// else :
	std::string all_normal_params(position, str_to_parse.begin() + colon_pos);

	t_parse_return ret = parse_normal_parameters(all_normal_params);
	if (ret != PARSING_SUCCESS)
		return (ret);

	std::string trailing_param(str_to_parse.begin() + colon_pos + 1, str_to_parse.end());
	if (trailing_param.empty() == false 
			&& trailing_param.find_first_not_of(' ') != std::string::npos)
		ret = this->add_parameter(trailing_param);
	return (ret);
}
