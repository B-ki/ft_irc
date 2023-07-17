/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:47:06 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/17 09:35:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constant.h"
#include "tests.h"
#include "parsing/Message.h"

int parsing_test_cmd(t_cmd_type expected_cmd, 
		std::vector<std::string> expected_params,
		std::map<std::string, std::string> expected_tags,
		std::string expected_prefix,
		Message &message)
{
	message.print_message();
	assert(message.get_tags() == expected_tags);
	assert(message.get_prefix() == expected_prefix);
	if (message.get_cmd() != expected_cmd)
	{
		std::cerr << "message.cmd = " << message.get_cmd();
		std::cerr << " / expected = " << expected_cmd << std::endl;
		return 3;
	}
	if (message.get_parameters() != expected_params)
	{
		std::vector<std::string> mess_param = message.get_parameters();
		std::cerr << "mess_param.size() = " << mess_param.size();
		std::cerr << " / expect.size() = " << expected_params.size() << std::endl;
		std::vector<std::string>::iterator it1;
		std::vector<std::string>::iterator it2 = expected_params.begin();
		for (it1 = mess_param.begin(); it1 != mess_param.end(); it1++, it2++)
		{
			std::cerr << "param : " << *it1 << "[sz:" << (*it1).size();
			std::cerr << "] / expected : " << *it2 << "[sz:" << (*it2).size();
			std::cerr << "]" << std::endl;
		}
		return 4;
	}
	return 0;
}

int parsing_test_1(void)
{
	std::string tested_string("PRIVMSG * LIST :");

	Message message;
	std::cout << "Tested string is : " << tested_string << std::endl;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_2(void)
{
	std::string tested_string("PRIVMSG * LS :multi-prefix sasl");
	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LS");
	expected_params.push_back("multi-prefix sasl");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_3(void)
{
	std::string tested_string("PRIVMSG :bla bla bla");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla bla bla");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_4(void)
{
	std::string tested_string("PRIVMSG           #chan    :Hey!");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back("Hey!");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_5(void)
{
	std::string tested_string("PRIVMSG #chan Hey!");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back("Hey!");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_6(void)
{
	std::string tested_string("PRIVMSG #chan ::-)");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back(":-)");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_7(void)
{
	std::string tested_string("PRIVMSG    ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_8(void)
{
	std::string tested_string("  KICK        :      ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_cmd = KICK;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_9(void)
{
	std::string tested_string(" MODE bla bla bla");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_cmd = MODE;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_10(void)
{
	std::string tested_string("       PRIVMSG     bla   bla bla  ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	t_cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_cmd = PRIVMSG;
	return (parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message));
}

int parsing_test_11(void)
{
	std::string tested_string(":SomeOp MODE #channel +oo SomeUser :AnotherUser");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix = "SomeOp";
	t_cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	expected_params.push_back("#channel");
	expected_params.push_back("+oo");
	expected_params.push_back("SomeUser");
	expected_params.push_back("AnotherUser");
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
		parsing_test_9,
		parsing_test_10,
		parsing_test_11,
	};
	std::string ret_type[5] = {	"SUCCESS", "TAGS ERROR", "PREFIX ERROR", 
		"CMD ERROR", "PARAM ERROR" };
	int ret = 0;

	for (int i = 0; i < 9; i++)
	{
		ret = (*funcptr[i])();
		std::cout << "Test number " << i  + 1 << " : ";
		if (ret == 0)
			std::cout << GREEN << ret_type[ret] << RESET << std::endl;
		else {
			std::cout << RED << ret_type[ret] << RESET << std::endl;
			assert(false);
		}
	}
}
