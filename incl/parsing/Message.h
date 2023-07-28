/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/27 00:00:20 by rmorel           ###   ########.fr       */
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
# include "error.h"

class Message
{
	public:
		// -- Constructors --
		Message(void);
		Message(std::string messageToParse);
		Message(Message const & src);

		// -- Destructor --
		~Message(void);

		Message & operator=(Message const & rhs);
		
		// -- Getter --
		std::string 						get_raw(void) const;
		std::map<std::string, std::string> 	get_tags(void) const;
		std::string 						get_prefix(void) const;
		cmd_type							get_cmd(void) const;
		const std::vector<std::string>& 	get_parameters(void) const;
		const std::string& 					get_command() const;

		// -- Public Functions --
		void 			print_message(void);
		void 			clear(void);
		int 			parse_message(std::string str_to_parse);
		
		enum parse_return
		{
			PARSING_SUCCESS = 0,
			PARSING_EMPTY_MESSAGE,
			PARSING_GRAMMAR_ERROR,
			PARSING_EXCEPT_ERROR
		};

	private:
		std::string 						_raw;
		std::map<std::string, std::string> 	_tags;
		std::string 						_prefix;
		cmd_type 							_cmd;
		std::vector<std::string> 			_parameters;
		std::string     			        _command;

		// -- Private functions --
		int 	parse_tags(std::string all_tags);
		int 	handle_tags(std::string &str_to_parse, 
		  					std::string::iterator &position, size_t &space_pos);
		int 	handle_prefix(std::string &str_to_parse,
							std::string::iterator &position, size_t &space_pos);
		int 	handle_no_trailing(std::string &str_to_parse,
							std::string::iterator &position, size_t &space_pos);
		int 	parse_normal_parameters(std::string normal_params);

		int 	add_raw(std::string raw);
		int 	add_tag(std::string key, std::string value);
		int 	add_prefix(std::string prefix);
		int 	add_cmd(std::string cmd_str);
		int 	add_parameter(std::string parameter);

};

#endif 
