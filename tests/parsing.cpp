/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:47:06 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 18:19:57 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void parsing_test_cmd(cmd_type expected_cmd, 
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
		assert(false);
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
		assert(false);
	}
}

void parsing_test_1(void)
{
	std::string tested_string("PRIVMSG * LIST :");

	Message message;
	std::cout << "Tested string is : " << tested_string << std::endl;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LIST");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_2(void)
{
	std::string tested_string("PRIVMSG * LS :multi-prefix sasl");
	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("*");
	expected_params.push_back("LS");
	expected_params.push_back("multi-prefix sasl");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_3(void)
{
	std::string tested_string("PRIVMSG :bla bla bla");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla bla bla");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_4(void)
{
	std::string tested_string("PRIVMSG           #chan    :Hey!");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back("Hey!");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_5(void)
{
	std::string tested_string("PRIVMSG #chan Hey!");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back("Hey!");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_6(void)
{
	std::string tested_string("PRIVMSG #chan ::-)");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#chan");
	expected_params.push_back(":-)");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_7(void)
{
	std::string tested_string("PRIVMSG    ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_8(void)
{
	std::string tested_string("  KICK        :      ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_cmd = KICK;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_9(void)
{
	std::string tested_string(" MODE bla bla bla");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_cmd = MODE;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_10(void)
{
	std::string tested_string("       PRIVMSG     bla   bla bla  ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_params.push_back("bla");
	expected_cmd = PRIVMSG;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_11(void)
{
	std::string tested_string(":SomeOp MODE #channel +oo SomeUser :AnotherUser");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix = "SomeOp";
	cmd_type expected_cmd;
	std::vector<std::string> expected_params;
	expected_params.push_back("#channel");
	expected_params.push_back("+oo");
	expected_params.push_back("SomeUser");
	expected_params.push_back("AnotherUser");
	expected_cmd = MODE;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_12(void)
{
	std::string tested_string(":SomeOp MODE");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix = "SomeOp";
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_13(void)
{
	std::string tested_string(":SomeOp       MODE");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix = "SomeOp";
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_14(void)
{
	std::string tested_string("     :SomeOp MODE");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix = "SomeOp";
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_15(void)
{
	std::string tested_string("MODE");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_16(void)
{
	std::string tested_string("MODE     ");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_17(void)
{
	std::string tested_string("   MODE");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd = MODE;
	std::vector<std::string> expected_params;
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test_18(void)
{
	std::string tested_string("   NICK wrong:nick:name");

	Message message;
	message.parse_message(tested_string);
	std::map<std::string, std::string> expected_tags;
	std::string expected_prefix;
	cmd_type expected_cmd = NICK;
	std::vector<std::string> expected_params;
	expected_params.push_back("wrong:nick:name");
	parsing_test_cmd(expected_cmd, expected_params, expected_tags,
				expected_prefix, message);
}

void parsing_test(std::vector<Test*>& tests)
{
	tests.push_back(new Test("Parsing 1", &parsing_test_1));
	tests.push_back(new Test("Parsing 2", &parsing_test_2));
	tests.push_back(new Test("Parsing 3", &parsing_test_3));
	tests.push_back(new Test("Parsing 4", &parsing_test_4));
	tests.push_back(new Test("Parsing 5", &parsing_test_5));
	tests.push_back(new Test("Parsing 6", &parsing_test_6));
	tests.push_back(new Test("Parsing 7", &parsing_test_7));
	tests.push_back(new Test("Parsing 8", &parsing_test_8));
	tests.push_back(new Test("Parsing 9", &parsing_test_9));
	tests.push_back(new Test("Parsing 10", &parsing_test_10));
	tests.push_back(new Test("Parsing 11", &parsing_test_11));
	tests.push_back(new Test("Parsing 12", &parsing_test_12));
	tests.push_back(new Test("Parsing 13", &parsing_test_13));
	tests.push_back(new Test("Parsing 14", &parsing_test_14));
	tests.push_back(new Test("Parsing 15", &parsing_test_15));
	tests.push_back(new Test("Parsing 16", &parsing_test_16));
	tests.push_back(new Test("Parsing 17", &parsing_test_17));
	tests.push_back(new Test("Parsing 18", &parsing_test_18));
}

