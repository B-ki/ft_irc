/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:10:19 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/22 18:47:31 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "constant.h"
# include "struct.h"
# include "error.h"

t_parse_return parse_tags(std::string tagStr, t_message *messageParsed)
{
	return (PARSING_SUCCESS);
}

t_parse_return parser(std::string strToParse, t_message *messageParsed)
{
	if (strToParse.empty())
	{
		return (PARSING_EMPTY_MESSAGE);
	}
	std::string::iterator position;
	std::string::iterator nextSpace;
	position= strToParse.begin();
	if (*position == '@')
	{
		size_t spacePos = strToParse.find(' ');
		std::string tagStr;
		if (spacePos != std::string::npos) {
			tagStr = std::string(it, it + spacePos);
		}
		else {
			tagStr = std::string(it, strToParse.end());;
		}
		t_parse_return ret = parse_tags(tagStr, messageParsed);
		if (ret != 0) {
			return (ret);
		}
		it += strToParse.find(' ');
	}
	if (*position == ':')
	{
	}
	std::string token = message.substr(0, spacePOs);

	return (PARSING_SUCCESS);
}
