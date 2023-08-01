#include <iostream>
#include <string>
#include <cstdlib>
#include <csignal>
#include "server/Server.h"

bool g_sig = true;

void	usage(const std::string& prog_name)
{
	std::cerr << "Usage: " << prog_name << " <port> <password>\n";
}

void    handle_sigint(int sig)
{
	(void)sig;
	INFO("SIGINT received, stoping server properly");
	g_sig = false;
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
	server.write_logo();
	server.start();
	signal(SIGINT, &handle_sigint);
	while(server.running() && g_sig)
		server.loop();
	server.stop();
	return 0;
}
