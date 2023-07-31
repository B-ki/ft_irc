#ifndef COMMAND_H
# define COMMAND_H

# include "server/Server.h"
# include "constant.h"
# include "utils.h"
# include "command/error_command.h"
# include "command/reply_command.h"


class Command
{
	public:
		// -- Constructors, Destructors && Operator --
		Command(void);
		Command(const Command& src);
		Command(Server* serv, Client* client, std::string raw_message);
		Command& operator=(const Command& rhs);

		// -- Destructor --
		~Command(void);

		// -- Getters & Setters --
		Server* get_server();
		Client* get_client();
		Message& get_message();

		// -- Error & replies --
		int reply(std::string message, int code);
		int welcome();

		// -- Execute --
		int execute_command();

	private:
		Server* _server;
		Client* _client;
		Message _message;

		// -- Commands --
		int execute_PASS();
		int execute_NICK();
		int execute_USER();
		int execute_JOIN();
		int execute_PART();
		int execute_KICK();
		int execute_INVITE();

		void    join_channel(const std::string& channel_name, const std::string& password);
};

#endif
