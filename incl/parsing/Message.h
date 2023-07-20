/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/20 11:27:43 by rmorel           ###   ########.fr       */
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
		std::vector<std::string> 			get_parameters(void) const;

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

		// -- Private functions --
		parse_return 	parse_tags(std::string all_tags);
		parse_return 	handle_tags(std::string &str_to_parse, 
		  				std::string::iterator &position, size_t &space_pos);
		parse_return 	handle_prefix(std::string &str_to_parse,
							std::string::iterator &position, size_t &space_pos);
		void 			skip_space(std::string::iterator &position, 
							size_t &space_pos);
		parse_return 	parse_normal_parameters(std::string normal_params);

		parse_return 	add_raw(std::string raw);
		parse_return 	add_tag(std::string key, std::string value);
		parse_return 	add_prefix(std::string prefix);
		parse_return 	add_cmd(std::string cmd_str);
		parse_return 	add_parameter(std::string parameter);

};

#endif 
