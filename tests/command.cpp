/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:06:18 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/19 20:21:37 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/error_command.h"
#include <unistd.h>
#include <cstring> 
#include <iostream>
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

	Server server;
	Client client(sv[1]);
	Command cmd(&server, &client, "NICK wron:gnick:name");	

	ssize_t num_bytes = read(sv[0], buf, sizeof(buf));
	if (num_bytes <= 0) {
		ERROR("Read");
		close(sv[0]);
		close(sv[1]);
		return ;
	}
	buf[num_bytes] = '\0';
	assert("wron:gnick:name :No such nick/channel" == buf);
	return;
}
