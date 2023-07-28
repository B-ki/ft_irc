/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:06:18 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 19:40:29 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring> 
#include "tests.h"
#include "CmdTest.hpp"

void command_test_1()
{
	CmdTest cmd_test;
	cmd_test.send("PASS password");
	cmd_test.send("NICK rmorel");
	cmd_test.send("USER rmorel");
	//std::string result = cmd_test.receive();
	//DEBUG("After PASS password, NICK rmorel and USER rmorel got [" << 
	//		result << "]");
	//DEBUG(cmd_test.get_server_hostname());
	//std::string expected = ":" + cmd_test.get_server_hostname() + 
	//	" rmorel :Welcome to the IRC Network rmorel"; 
	//assert(result == expected);
	DEBUG("Segfault? ");
}


void command_test_all(std::vector<Test*>& tests)
{
	(void)tests;
	//tests.push_back(new Test("Welcome message", &command_test_1));	
}
