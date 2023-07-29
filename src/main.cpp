#include <iostream>
#include <string>
#include "server/Server.h"
#include <stdlib.h>

void	usage(std::string prog_name)
{
	std::cerr << "Usage: " << prog_name << " <port> <password>\n";
}

int	main(int ac, char **av)
{
	if (ac != 3) {
		usage(av[0]);
		exit(1);
	}
	if (!Server::is_valid_port(av[1])) {
		std::cerr << "Invalid port number\n";
		exit(2);
	}
	if (!Server::is_valid_password(av[2])) {
		std::cerr << "Invalid password\n";
		exit(3);
	}
	Server server = Server(av[1], av[2]);
	server.start();
	while(server._started)
		server.loop();
	return 0;
}
