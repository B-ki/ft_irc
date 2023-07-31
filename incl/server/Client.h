#ifndef CLIENT_H
#define CLIENT_H 

# include <sys/socket.h>
# include <string.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string>
# include <vector>
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
		int                             get_fd() const;
		const sockaddr_storage*         get_storage_addr() const;
		socklen_t*                      get_addr_len();
		const char*                     get_IP() const;
		const std::string&              get_nick() const;
		const std::string&              get_user() const;
		const std::string&              get_real_name() const;
		const std::string&              get_last_message() const;
		bool                  		    is_authenticated() const;
		bool 						    has_given_password() const;
		bool 						    has_given_one_name() const;
		const std::string 			    get_source() const;
		const std::vector<std::string>& get_channels() const;

		// -- Setter --
		void    set_fd(int fd);
		void    set_IP();
		void    set_nick(const std::string& new_nick);
		void    set_user(const std::string& new_user);
		void    set_real_name(const std::string& new_real_name);
		void    set_authenticated(bool value);
		void    set_password_ok(bool const value);
		void    set_name_given(bool const value);


		// -- Public functions --
		void        add_channel(const std::string& channel);
		void        remove_channel(const std::string& channel);
		int         read_buffer();
		int         send_to(const Client& client, const std::string& message) const;
		int 		send(const std::string& message) const;
		int 		reply(const std::string& message, int code) const;
		bool        has_message() const;
		std::string extract_message();

	private:
		// -- Private attributes --
		int 				        _fd;
		sockaddr_storage 	        _sock_addr;
		char 				        _ip[NI_MAXHOST];
		socklen_t 			        _addrlen;
		std::string 		        _nick;
		std::string 		        _user;
		std::string 		        _real_name;
		Buffer 				        _buffer;
		bool 				        _authenticated;
		bool 				        _name_given;
		bool 				        _pwd_ok;
		std::string 		        _last_message;
		std::vector<std::string>    _channels;

		// -- Private functions --

};

#endif 
