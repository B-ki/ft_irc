#ifndef CMDTEST_H
# define CMDTEST_H

#include "tests.h"

class CmdTest
{
	public:
		// -- Constructors, Destructors && Operator --
		CmdTest(const std::string& port, const std::string& password);
		CmdTest(const CmdTest& src);
		~CmdTest(void);
		CmdTest& operator=(const CmdTest& rhs);

		void send(const std::string& tested);
		const std::string receive();
		void stop();

	private:
		Server      _server;
		pthread_t   _server_thread_id;
		int         _client_fd;
};

#endif
