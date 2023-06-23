/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:04:54 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/23 19:09:15 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP 

# include "constant.h"
# include <string>
# include <map>
# include <vector>

class Message
{
	public:
		Message(void);
		Message(std::string messageToParse);
		Message(Message const & src);
		~Message(void);

		Message & operator=(Message const & rhs);
		
		std::string getRaw(void) const;
		std::map<std::string, std::string> getTags(void) const;
		std::string getPrefix(void) const;
		t_cmd_type getCmd(void) const;
		std::vector<std::string> getParameters(void) const;

		t_parse_return addRaw(std::string raw);
		t_parse_return addTag(std::string tag);
		t_parse_return addPrefix(std::string prefix);
		t_parse_return addCmd(t_cmd_type cmd);
		t_parse_return addParameter(std::string parameter);

	private:
		std::string 						raw;
		std::map<std::string, std::string> 	tags;
		std::string 						prefix;
		t_cmd_type 							cmd;
		std::vector<std::string> 			parameters;
};

#endif 
