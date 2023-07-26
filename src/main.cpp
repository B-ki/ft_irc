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

	Server server = Server(av[1], av[2]);
	server.start();
	if (server._started)
		std::cout << "Server started." << std::endl;
	while(server._started)
	{
		server.loop();
	}
	return 0;
}
