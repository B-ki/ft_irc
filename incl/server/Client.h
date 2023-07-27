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
		//Client(const Client& other);
		//Client& operator=(const Client& other);

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
		bool 						has_given_pwd() const;
		const std::string 			get_source() const;

		// -- Setter --
		void set_fd(int fd);
		void set_IP();
		void set_nick(const std::string& new_nick);
		void set_user(const std::string& new_user);
		void set_real_name(const std::string& new_real_name);
		void set_pwd_ok(bool value);
		void set_authenticated(bool value);

		// -- Public functions --
		int read_buffer();
		int send(const std::string& message) const;
		int reply(const std::string& message, int code) const;

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
		bool 				_pwd_ok;
		std::string 		_last_message;

};

#endif 
