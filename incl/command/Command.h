#ifndef COMMAND_H
# define COMMAND_H

# include "server/Server.h"
# include "constant.h"
# include "utils.h"
# include "command/error_command.h"
# include "command/reply_command.h"
# include "struct.h"


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
		int execute_TOPIC();
		int execute_PRIVMSG();
		int execute_NOTICE();
		int execute_MODE();
		int user_MODE(const std::string& target);
		int channel_MODE(const std::string& target);

		void    join_channel(const std::string& channel_name, const std::string& password);
};

#endif
