/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:57:40 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 18:23:15 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdTest.hpp"

CmdTest::CmdTest() : _client(),	_server()
{
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, _sv) == -1) {
		ERROR("socketpair");
		exit(1);
	}
	std::cout << "Socket_pair = [" << _sv[0] << ", " << _sv[1] << "]\n";

	_client.set_fd(_sv[1]);
}

CmdTest::~CmdTest()
{
	close(_sv[0]);
	close(_sv[1]);
}

const std::string CmdTest::receive()
{

	ssize_t num_bytes = read(_sv[0], _buf, sizeof(_buf));
	if (num_bytes <= 0) {
		ERROR("Read");
		return "";
	}

	_buf[num_bytes] = '\0';
	std::string result(_buf);
	return result;
}

void CmdTest::send(const std::string& tested)
{
	INFO( "Tested string is : " << tested);
	Command cmd(&_server, &_client, tested);	

	cmd.execute_command();
}

const std::string CmdTest::get_server_hostname()
{
	return _server.get_hostname();
}
