/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:10:19 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/26 19:24:46 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "constant.h"
# include "struct.h"
# include "error.h"
# include "Message.hpp"
#include <exception>

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

t_parse_return parse_tags(std::string all_tags, Message &message)
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
			message.add_tag(tag.first, tag.second);
			start_index = end_index + 1;
		}
	}
	return (PARSING_SUCCESS);
}

t_parse_return parse_normal_parameters(std::string normal_params, Message &message)
{
	int start_index = 0;
	int end_index = 0;

	for (std::string::size_type i = 0; i < all_tags.size(); i++)
	{
		if (normal_params[i] == ' ')
		{
			end_index = i;
			std::string temp;
			temp.append(normal_params, start_index, end_index - start_index);
			while (normal_params[i] && normal_params[i++] == ' ')
				end_index++;
			if (message.add_parameter(temp) == PARSING_GRAMMAR_ERROR)
				return (PARSING_GRAMMAR_ERROR);
			start_index = end_index + 1;
		}
	}
	return (PARSING_SUCCESS);

}

t_parse_return parse_parameters(std::string param_str, Message &message)
{
	return (PARSING_SUCCESS);
}

t_parse_return parser(std::string str_to_parse, Message &message)
{
	if (str_to_parse.empty())
		return (PARSING_EMPTY_MESSAGE);
	std::string::iterator position;
	std::string::iterator nextSpace;
	size_t space_pos = 0;
	position= str_to_parse.begin();

	// Check if tags are presents
	if (*position == '@') {
		space_pos = str_to_parse.find(' ', space_pos);
		std::string tag_str;

		if (space_pos != std::string::npos)
			tag_str = std::string(position, position + space_pos);
		else 
			return (PARSING_GRAMMAR_ERROR);
		t_parse_return ret = parse_tags(tag_str, message);
		if (ret != 0)
			return (ret);
		position += space_pos;
	}

	// Skip spaces
	while (*(position++) == ' ')
		space_pos++;

	// Check if prefix are presents
	if (*position == ':') {
		space_pos = str_to_parse.find(' ', space_pos);
		std::string prefix_str;

		if (space_pos != std::string::npos)
			prefix_str = std::string(position, position + space_pos);
		else 
			return (PARSING_GRAMMAR_ERROR);
		message.add_prefix(prefix_str);
		position += space_pos;
	}

	// Skip spaces
	while (*(position++) == ' ')
		space_pos++;

	// Check if there is nothing after the command
	space_pos = str_to_parse.find(' ', space_pos);

	if (space_pos == std::string::npos) {
		std::string cmd_str = std::string(position, str_to_parse.end());
		return (message.add_cmd(cmd_str));
	}

	// If something after cmd, we expect some parameters
	// But first we parse the cmd
	std::string cmd_str = std::string(position, position + space_pos);

	if (message.add_cmd(cmd_str) == PARSING_GRAMMAR_ERROR)
		return (PARSING_GRAMMAR_ERROR);

	// Skip spaces
	while (*(position++) == ' ')
		space_pos++;

	std::string::size_type colon_pos = str_to_parse.find(':', space_pos);

	// all_normal_params is a string until the ':' or the end if no trailing
	std::string all_normal_params(position, position + colon_pos);

	// if no trailing parameter :
	if (colon_pos == std::string::npos)
	{
		return (parse_normal_parameters(all_normal_params, message));
		/*
		space_pos = str_to_parse.find(' ', space_pos);

		// Parse all parameter except the last one
		while (space_pos != std::string::npos) {
			std::string param_str = std::string(position, position + space_pos);
			if (message.add_parameter(param_str) == PARSING_GRAMMAR_ERROR)
				return (PARSING_GRAMMAR_ERROR);
			position += space_pos;
			while (*position == ' ')
				position ++;
			space_pos = str_to_parse.find(' ', space_pos);	
		}

		// Last parameter
		std::string param_str = std::string(position, str_to_parse.end());
		if (message.add_parameter(param_str) == PARSING_GRAMMAR_ERROR)
			return (PARSING_GRAMMAR_ERROR);
			*/
	}

	// else :
	std::string trailing_param(position + colon_pos + 2, str_to_parse.end());
	return (message.add_parameter(trailing_param));
}

