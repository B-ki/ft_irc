/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTest.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:52:55 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 18:15:18 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CMDTEST_H
# define CMDTEST_H

#include "tests.h"

class CmdTest
{
	public:
		// -- Constructors, Destructors && Operator --
		CmdTest();
		CmdTest(const CmdTest& src);
		~CmdTest(void);
		CmdTest& operator=(const CmdTest& rhs);

		std::string cmd_return();
		void send(const std::string& tested);
		const std::string receive();
		const std::string get_server_hostname();

	private:
		char _buf[1024];
		int _sv[2];
		Client _client;
		Server _server;

};

#endif
