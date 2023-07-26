#ifndef CLIENT_H
#define CLIENT_H 

# include <sys/socket.h>
# include <string.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string>
# include "server/Buffer.h"

class Client
{
	public:
		// -- Constructors --
		Client();
		Client(int fd);
		Client(const Client& other);
		Client& operator=(const Client& other);

		// -- Destructors --
		~Client();

		// -- Getter --
		int                         get_fd() const;
		const sockaddr_storage*     get_storage_addr() const;
		socklen_t*                  get_addr_len();
		const char*                 get_IP() const;
		const std::string&          get_nick() const;
		const std::string&          get_user() const;
		const std::string&          get_real_name() const;
		const std::string&          get_last_message() const;
		bool                        is_authenticated() const;

		// -- Setter --
		void set_fd(int fd);
		void set_IP();
		void set_nick(std::string const new_nick);
		void set_user(std::string const new_user);
		void set_real_name(std::string const new_real_name);
		void set_authenticated(bool const value);

		// -- Public functions --
		int read_buffer();
		int send(std::string const message);

	private:
		// -- Private attributes --
		int 				_fd;
		sockaddr_storage 	_sock_addr;
		char 				_ip[NI_MAXHOST];
		socklen_t 			_addrlen;
		std::string 		_nick;
		std::string 		_user;
		std::string 		_real_name;
		Buffer 				_buffer;
		bool 				_authenticated;
		std::string 		_last_message;

};

#endif 
