/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:06:18 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 15:13:01 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring> 
#include "tests.h"
#include "CmdTest.hpp"


void command_test_1()
{
	CmdTest cmd_test("PASS 123", "PASS 123");
	cmd_test.test();
}

void command_test_2()
{
	CmdTest cmd_test("PASS 123", "PASS 123");
	cmd_test.test();
}
