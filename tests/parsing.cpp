/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:47:06 by rmorel            #+#    #+#             */
/*   Updated: 2023/06/28 17:27:27 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constant.h"
#include "core/color.h"
# include "tests.h"
# include "Message.hpp"
# include "error.h"

int parsing_test_cmd(t_cmd_type expected_cmd, 
		std::vector<std::string> expected_params,
		std::map<std::string, std::string> expected_tags,
		std::string expected_prefix,
		Message &message)
{
	message.print_message();
	DEBUG("After printing");
	if(message.get_tags() != expected_tags)
		return 1;
	if (message.get_prefix() != expected_prefix)
		return 2;
	if (message.get_cmd() != expected_cmd)
	{
		std::cerr << "message.cmd = " << message.get_cmd();
		std::cerr << " / expected = " << expected_cmd << std::endl;
		return 3;
	}
	if (message.get_parameters() != expected_params)
		return 4;
	return 0;
}

int parsing_test_1(void)
{
	std::string tested_string("PRIVMSG * LIST :");

	Message message;
	std::cout << "Tested string is : " << tested_string << std::endl;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_2(void)
{
	std::string tested_string("PRIVMSG * LS :multi-prefix sasl");
	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_3(void)
{
	std::string tested_string("PRIVMSG :bla bla bla");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_4(void)
{
	std::string tested_string("PRIVMSG #chan :Hey!");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_5(void)
{
	std::string tested_string("PRIVMSG #chan Hey!");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_6(void)
{
	std::string tested_string("PRIVMSG #chan ::-)");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_7(void)
{
	std::string tested_string("PRIVMSG ");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_8(void)
{
	std::string tested_string("PRIVMSG :");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_9(void)
{
	std::string tested_string("PRIVMSG bla bla bla");

	Message message;
	message.parse_raw_string(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_params.push_back("");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

void parsing_all_test(void)
{
	int (*funcptr[])() = 
	{
		parsing_test_1,
		parsing_test_2,
		parsing_test_3,
		parsing_test_4,
		parsing_test_5,
		parsing_test_6,
		parsing_test_7,
		parsing_test_8,
		parsing_test_9
	};
	std::string ret_type[5] = {	"SUCCESS", "TAGS ERROR", "PREFIX ERROR", 
		"CMD ERROR", "PARAM ERROR" };
	int ret = 0;

	for (int i = 0; i < 9; i++)
	{
		ret = (*funcptr[i])();
		std::cout << "Test number " << i << " : ";
		std::cout << "[ret = " << ret << "] ";
		if (ret == 0)
			std::cout << GREEN << ret_type[ret] << std::endl;
		else {
			std::cout << RED << ret_type[ret] << std::endl;
			assert(false);
		}
	}
}
