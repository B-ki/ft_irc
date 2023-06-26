#ifndef CONNECTION_H
# define CONNECTION_H

# include <netdb.h>

class	Connection {
	public:
		Connection();
		Connection(const Connection& conn);
		Connection&	operator=(const Connection& conn);

		~Connection();

	private:
		char				ip4[INET_ADDRSTRLEN];
		struct sockaddr_in	sa;

		char				ip6[INET6_ADDRSTRLEN];
		struct sockaddr_in6	sa6;
};

#endif