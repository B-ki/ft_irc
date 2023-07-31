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

		void                create_client();
		void                send(size_t id, const std::string& tested);
		const std::string   receive(size_t id);
		void                stop();

	private:
		Server              _server;
		std::string         _port;
		pthread_t           _server_thread_id;
		std::vector<int>    _clients_fd;
};

#endif
