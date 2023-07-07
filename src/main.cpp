#include <iostream>
#include <netinet/in.h>
#include <string>
#include <numeric>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "error.h"
#include "server/Server.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

#define MAX_CONNEXIONS 10

void	start_server(std::string port)
{
	int					sockfd;
	int					yes=1;
	struct addrinfo		hints;
	struct addrinfo*	servinfo;
	void*							addr;
	char							ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port.c_str(), &hints, &servinfo) != 0) {
		ERROR("can't get addr infos");
		exit(2);
	}

	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (sockfd == -1) {
		ERROR("can't create the socket FD");
		exit(3);
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		ERROR("can't set socket options");
		exit(4);
	}

	if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		ERROR("can't bind the socket");
		exit(5);
	}

	if (listen(sockfd, MAX_CONNEXIONS) == -1) {
		ERROR("can't listen to the specified port " + port);
		exit(6);
	}

	struct sockaddr_in*	ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
	addr = &(ipv4->sin_addr);
	inet_ntop(servinfo->ai_family, addr, ipstr, sizeof(ipstr));

	std::cout << "Server in now waiting for connections on: " << ipstr << ":" << port << std::endl;
	freeaddrinfo(servinfo);
	close(sockfd);
	INFO("Releasing the socket");
}

void	usage(std::string prog_name)
{
	std::cerr << "Usage: " << prog_name << " <port> <password>\n";
}

int	main(int ac, char **av)
{
	//Server	server;

	if (ac != 3) {
		usage(av[0]);
		exit(1);
	}

	Server server = Server(av[1], av[2]);
	server.start();
	std::cout << server._started << std::endl;
	while(server._started)
	{
		server.loop();
	}
	return 0;
}
