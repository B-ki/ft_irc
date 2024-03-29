#ifndef SERVER_H
# define SERVER_H

# include <string>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <poll.h>
# include <netdb.h>
# include <stdlib.h>
# include <vector>
# include <unistd.h>
# include <map>
# include <iomanip>
# include "error.h"
# include "color.h"
# include "Client.h"
# include "management/Channel.h"
# include "parsing/Message.h"
# include "Bot.h"
# include "RockPaperScissorsBot.h"
# include <fstream>

# define SERVER_NAME "ft_irc"
# define SERVER_VERSION "v1.0"
# define MAX_CONNEXIONS 10

class	Server {
	public:
		// -- Constructors --
		Server(const std::string& port, const std::string& password);

		// -- Destructor --
		~Server();

		// -- Getter --
		Client* 			    get_client(int fd);
		const Client* 			get_client(int fd) const;
		Client* 			    get_client(const std::string& nick);
		const Client* 			get_client(const std::string& nick) const;
		const std::string& 		get_password() const;
		std::map<int, Client>& 	get_client_list();
		const std::string&      get_name() const;
		const std::string&      get_version() const;
		bool 					is_sending_welcome_msg() const;

		// -- Public Functions --
		int		    start();
		int		    stop();
		int 	    loop();
		int 	    create_client();
		void 	    print_clients();
		bool        channel_exists(std::string name);
		bool        nick_already_used(const std::string& nick) const;
		int         create_channel(Client* client, const std::string& name);
		Channel*    get_channel(const std::string& name);
		const Bot*  get_bot(const std::string& name) const;
		bool        running() const;
		void        delete_channel(const std::string& name);
		std::string get_date_time() const;
		std::string get_user_modes() const;
		std::string get_channel_modes() const;
		void 		write_logo() const;
		void 		send_welcome_msg(bool value);

		// -- Public static functions --
		static bool		is_valid_port(const std::string& port);
		static bool		is_valid_password(const std::string& password);

	private:
		// -- Private attributes --
		int						        _sockfd;
		int						        _nb_clients;
		bool	                        _started;
		time_t                          _created_at;
		std::string				        _port;
		std::string				        _password;
		std::string 				    _name;
		std::string 				    _version;
		struct addrinfo			        _hints;
		struct addrinfo*		        _servinfo;
		pollfd 	                        _client_pfd_list[MAX_CONNEXIONS];
		std::map<int, Client> 	        _client_list;
		std::map<std::string, Channel>  _channels;
		std::vector<Bot*>               _bots;
		bool 							_send_welcome_msg;

		// -- Private functions --
		int						handle_recv(int fd, int i);
		void                    remove_fd(int start);
		int 	                delete_client(int id);
};

#endif
