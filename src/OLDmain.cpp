#include <asm-generic/socket.h>
#include <iostream>
#include "error.h"
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <poll.h>
#include <vector>

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	std::cout << "Bonjour" << std::endl;
	std::string ipAddress = "127.0.0.1";
	int port = 5000;
	int buffsize = 1024;
	char buffer[buffsize];

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		std::cout << "Failed to create socket fd. " << strerror(errno) << std::endl;
	}

	std::cout << "Creating socket on fd = " << sock_fd << std::endl;

	int opt = 1;

	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		std::cout << "Failed to set REUSEADDR option. " << strerror(errno) << std::endl;
		return 1;
	}

	struct sockaddr_in my_addr;

	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htons(INADDR_ANY);
	//inet_pton(AF_INET, ipAddress.c_str(), &my_addr.sin_addr); 
	my_addr.sin_port = htons(port);

	if (bind(sock_fd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)	{
		std::cout << "Could not bind sock_fd. " << strerror(errno) << std::endl;
		return 1;
	}

	std::cout << "Listening with protocol TCP on port " << port << std::endl;

	if (listen(sock_fd, SOMAXCONN) == -1)
		return 1;

	struct sockaddr_in client;
	
	socklen_t clientSize = sizeof(client);
	
	std::cout << "Waiting for a connection ...\n";
	int client_fd = accept(sock_fd, (struct sockaddr *) &client, &clientSize);
	if (client_fd == 1) {
		std::cout << "Failed to create client fd. " << strerror(errno) << std::endl;
	}

	memset(buffer, 0, buffsize);

	int MAX_CLIENT = 5;

	std::vector<pollfd> poll_fds;

	int ret_poll = 0;
	
	while (1) {
		ret_poll = poll(&poll_fds[0], poll_fds.size(), -1);
		if (ret_poll <= 0)
			continue;

		if (

	}
	/*
	bool isExit = false;
	while (client_fd > 0)
	{
		strcpy(buffer, "Server connected...\n");
		send(client_fd, buffer, buffsize, 0);

		std::cout << "Connected with client..." << std::endl;
		std::cout << "Enter # to end the connection" << std::endl;
		std::cout << "Client: ";
		do {
			memset(buffer, 0, buffsize);
			recv(client_fd, buffer, buffsize, 0);
			std::cout << buffer;
			if (*buffer == '#')
			{
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != '*');

		do {
			std::cout << "\nServer: ";
			do {
				memset(buffer, 0, buffsize);
				std::cin >> buffer;
				send(client_fd, buffer, buffsize, 0);
				if (*buffer == '#')
				{
					send(client_fd, buffer, buffsize, 0);
					*buffer = '*';
					isExit = true;
				}
			} while (*buffer != '*');

			std::cout << "Client: ";
			do {
				memset(buffer, 0, buffsize);
				recv(client_fd, buffer, buffsize, 0);
				std::cout << "Client: " << buffer;
				if (*buffer == '#')
				{
					*buffer = '*';
					isExit = true;
				}
			} while (*buffer != '*');
		} while (isExit == false);
		std::cout << "\n\n=> Connection terminated with IP " << inet_ntoa(client.sin_addr);
		close(client_fd);
		isExit = false;
		exit(1);
	}
	*/

	close(sock_fd);	
	std::cout << "Au revoir" << std::endl;
	return 0;
}
