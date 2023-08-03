/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message_parsing.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:37:52 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/31 11:42:03 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/Message.h"

void skip_space(std::string::iterator &position, size_t &space_pos)
{
	while (*(position) == ' ') {
		position++;
		space_pos++;
	}
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

int Message::parse_tags(std::string all_tags)
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

int Message::handle_tags(std::string &str_to_parse, 
		std::string::iterator &position, size_t &space_pos)
{
	space_pos = str_to_parse.find(' ', space_pos);
	std::string tag_str;

	if (space_pos != std::string::npos)
		tag_str = std::string(position, position + space_pos);
	else 
		return (PARSING_GRAMMAR_ERROR);
	int ret = this->parse_tags(tag_str);
	if (ret != 0)
		return (ret);
	position += space_pos;
	skip_space(position, space_pos);
	if (str_to_parse.find_first_not_of(' ', space_pos) == std::string::npos)
		return (PARSING_GRAMMAR_ERROR);
	return (PARSING_SUCCESS);
}

int Message::handle_prefix(std::string &str_to_parse,
		std::string::iterator &position, size_t &space_pos)
{
	space_pos = str_to_parse.find(' ', space_pos);
	std::string prefix_str;

	if (space_pos != std::string::npos)
		prefix_str = std::string(position + 1, str_to_parse.begin() + space_pos);
	else 
		return (PARSING_GRAMMAR_ERROR);
	this->add_prefix(prefix_str);
	while (position != str_to_parse.end() && *position != ' ')
		position++;
	skip_space(position, space_pos);
	if (str_to_parse.find_first_not_of(' ', space_pos) == std::string::npos)
		return (PARSING_GRAMMAR_ERROR);
	return (PARSING_SUCCESS);
}

int Message::parse_normal_parameters(std::string normal_params)
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

int Message::handle_no_trailing(std::string &str_to_parse,
		std::string::iterator &position, size_t &space_pos)
{
	skip_space(position, space_pos);
	std::string all_normal_params(position, str_to_parse.end());
	return (parse_normal_parameters(all_normal_params));
}

int Message::parse_message(std::string str_to_parse)
{
	if (str_to_parse.empty())
		return (PARSING_EMPTY_MESSAGE);
	this->add_raw(str_to_parse);

	std::string::iterator position;
	size_t space_pos = 0;
	position = str_to_parse.begin();
	const std::string::iterator start = str_to_parse.begin();

	skip_space(position, space_pos);
	if (*position == '@') {
		int ret = handle_tags(str_to_parse, position, space_pos);
		if (ret != PARSING_SUCCESS) {
			ERROR("parsing tags");
			return (ret);
		}
	}
	if (*position == ':') {
		int ret = handle_prefix(str_to_parse, position, space_pos);
		if (ret != PARSING_SUCCESS) {
			ERROR("parsing prefix");
			return (ret);
		}
	}
	skip_space(position, space_pos);

	space_pos = str_to_parse.find(' ', space_pos);
	if (space_pos == std::string::npos)
		return (this->add_cmd(std::string(position, str_to_parse.end())));

	if (this->add_cmd(std::string(position, str_to_parse.begin() + space_pos)) 
			== PARSING_GRAMMAR_ERROR) {
		return (PARSING_GRAMMAR_ERROR);
	}
	while (position != str_to_parse.end() && *position != ' ')
		position++;

	std::string::size_type trailing_pos = str_to_parse.find(" :", space_pos);

	if (trailing_pos == std::string::npos)
		return (handle_no_trailing(str_to_parse, position, space_pos));

	std::string normal_params(position, start + trailing_pos);
	if (int ret = parse_normal_parameters(normal_params))
		return (ret);
	std::string trailing_param(start + trailing_pos + 2, str_to_parse.end());
	if (trailing_param.find_first_not_of(' ') == std::string::npos)
		return(this->add_parameter(""));
	return(this->add_parameter(trailing_param));
	return (PARSING_SUCCESS);
}
