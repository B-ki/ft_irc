#ifndef MODE_PARSER_H
# define MODE_PARSER_H

# include "server/Server.h"

class ModeParser
{
	public:
		// -- Public Constructors, Destructors && Operator --
		ModeParser(const std::string& modestring, Channel* target, Server* server, Client* client,
				   const std::vector<std::string>& args);
		~ModeParser(void);

		// -- Public functions --
		int 	execute();

	private:
		// -- Private Attributes --
		Channel* 					    _target;
		std::string 				    _modestring;
		const std::vector<std::string>& _args;
		size_t                          _index;
		bool 						    _operand;
		bool 						    _last_operand;
		bool 						    _t_is_set;
		bool 						    _i_is_set;
		bool 						    _l_is_set;
		bool 						    _k_is_set;
		bool 						    _o_is_set;
		std::string 				    _modestring_reply;
		std::vector<std::string> 	    _args_reply;
		Server* 					    _server;
		Client* 					    _client;

		// -- Private functions --
		void 	    invite_only_channel_mode();
		void 	    protected_topic_mode();
		void 	    client_limit_mode();
		void 	    oper_user_mode();
		void 	    key_channel_mode();
		void 	    add_to_modestring_reply(const std::string& mode);
		void 	    add_to_args_reply(const std::string& arg);
		std::string MODE_reply();
		int 		reply(const std::string& message, int code);
};

#endif
