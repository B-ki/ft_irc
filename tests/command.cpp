/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:06:18 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/24 21:11:02 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/error_command.h"
#include <cstring> 
#include "command/Command.h"
#include "tests.h"

void test_error_function()
{
	int 	sv[2];
	char 	buf[1024];

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
		ERROR("socketpair");
		return;
	}
	std::cout << "Socket_pair = [" << sv[0] << ", " << sv[1] << "]\n";

	Server server;
	Client client(sv[1]);
	std::string test_string = "NICK wron:gnick:name";
	std::cout << "Tested string is : " << test_string << std::endl;
	Command cmd(&server, &client, test_string);	

	cmd.execute_command();

	ssize_t num_bytes = read(sv[0], buf, sizeof(buf));
	if (num_bytes <= 0) {
		ERROR("Read");
		close(sv[0]);
		close(sv[1]);
		return ;
	}

	buf[num_bytes] = '\0';
	std::string result(buf);
	assert(" wron:gnick:name :Erroneous nickname" == result);
	return;
}
