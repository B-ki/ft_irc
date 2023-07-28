/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:57:40 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 15:11:35 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdTest.hpp"

CmdTest::CmdTest(std::string tested, std::string expected) : _client(), 
	_server(), _tested(tested), _expected(expected)
{
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, _sv) == -1) {
		ERROR("socketpair");
		exit(1);
	}
	std::cout << "Socket_pair = [" << _sv[0] << ", " << _sv[1] << "]\n";

	_client.set_fd(_sv[1]);
}

void CmdTest::test()
{
	INFO( "Tested string is : " << _tested);
	Command cmd(&_server, &_client, _tested);	

	cmd.execute_command();

	ssize_t num_bytes = read(_sv[0], _buf, sizeof(_buf));
	if (num_bytes <= 0) {
		ERROR("Read");
		return;
	}

	_buf[num_bytes] = '\0';
	std::string result(_buf);
	assert(result == _expected);
}
