/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/26 18:34:22 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP 

# include "constant.h"
# include <string>
# include <map>
# include <vector>
# include <algorithm>

class Message
{
	public:
		Message(void);
		Message(std::string messageToParse);
		Message(Message const & src);
		~Message(void);

		Message & operator=(Message const & rhs);
		
		std::string get_raw(void) const;
		std::map<std::string, std::string> get_tags(void) const;
		std::string get_prefix(void) const;
		t_cmd_type get_cmd(void) const;
		std::vector<std::string> get_parameters(void) const;

		t_parse_return add_raw(std::string raw);
		t_parse_return add_tag(std::string key, std::string value);
		t_parse_return add_prefix(std::string prefix);
		t_parse_return add_cmd(std::string cmd_str);
		t_parse_return add_parameter(std::string parameter);

	private:
		std::string 						raw;
		std::map<std::string, std::string> 	tags;
		std::string 						prefix;
		t_cmd_type 							cmd;
		std::vector<std::string> 			parameters;
};

#endif 
