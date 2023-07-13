/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/13 12:13:48 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP 

# include "constant.h"
# include <string>
# include <map>
# include <vector>
# include <algorithm>
# include <iostream>

class Message
{
	public:
		// -- Constructor & Destructor --
		Message(void);
		Message(std::string messageToParse);
		Message(Message const & src);
		~Message(void);

		Message & operator=(Message const & rhs);
		
		// -- Getter --
		std::string get_raw(void) const;
		std::map<std::string, std::string> get_tags(void) const;
		std::string get_prefix(void) const;
		/* A voir si on garde, pas forcément besoin de parse le prefix
		std::string get_nick(void) const;
		std::string get_user(void) const;
		std::string get_host(void) const;
		*/
		t_cmd_type get_cmd(void) const;
		std::vector<std::string> get_parameters(void) const;

		void print_message(void);
		void clear(void);
		t_parse_return parse_message(std::string str_to_parse);
		

	private:
		std::string 						_raw;
		std::map<std::string, std::string> 	_tags;
		std::string 						_prefix;
		/*
		std::string 						_nick;
		std::string 						_user;
		std::string 						_host;
		*/
		t_cmd_type 							_cmd;
		std::vector<std::string> 			_parameters;

		// -- Private functions --
		
		t_parse_return parse_tags(std::string all_tags);
		t_parse_return handle_tags(std::string &str_to_parse, 
			std::string::iterator &position, size_t &space_pos);
		t_parse_return handle_prefix(std::string &str_to_parse,
			std::string::iterator &position, size_t &space_pos);
		void skip_space(std::string::iterator &position, size_t &space_pos);
		t_parse_return parse_normal_parameters(std::string normal_params);

		t_parse_return add_raw(std::string raw);
		t_parse_return add_tag(std::string key, std::string value);
		t_parse_return add_prefix(std::string prefix);
		/* A voir si on garde, pas forcément besoin de parse le prefix
		t_parse_return add_nick(std::string nick);
		t_parse_return add_user(std::string user);
		t_parse_return add_host(std::string host);
		*/
		t_parse_return add_cmd(std::string cmd_str);
		t_parse_return add_parameter(std::string parameter);

};

#endif 
