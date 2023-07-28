/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTest.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:52:55 by rmorel            #+#    #+#             */
/*   Updated: 2023/07/28 15:11:28 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CMDTEST_H
# define CMDTEST_H

#include "tests.h"

class CmdTest
{
	public:
		// -- Constructors, Destructors && Operator --
		CmdTest(std::string tested, std::string expected);
		CmdTest(const CmdTest& src);
		~CmdTest(void);
		CmdTest& operator=(const CmdTest& rhs);

		std::string cmd_return();
		void test();

	private:
		char _buf[1024];
		int _sv[2];
		Client _client;
		Server _server;
		std::string _tested;
		std::string _expected;

};

#endif
