#include "server/Server.h"
#include "command/Command.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <utility>
#include <ctime>

Server::Server(const std::string& port, const std::string& password) :
	_sockfd(-1), _nb_clients(0), _started(false), _created_at(time(NULL)), _port(port),
	_password(password), _name(SERVER_NAME), _version(SERVER_VERSION),
	_hints(), _servinfo(NULL), _client_pfd_list(), _client_list(), _channels(), _bots()
{
	INFO((std::string)"using the given port " + _port);
	INFO((std::string)"using the given password '" + _password + "'");
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _port.c_str(), &_hints, &_servinfo) != 0) {
		ERROR("could not get the server connection details");
		exit(1);
	}
	Bot* bot = new RockPaperScissorsBot("rpsbot");
	_bots.push_back(bot);
}

Server::~Server()
{
	this->stop();
	freeaddrinfo(_servinfo);
	for (std::vector<Bot*>::iterator it = _bots.begin(); it != _bots.end(); ++it)
		delete *it;
	INFO("destroying server");
}

int	Server::stop()
{
	if (_started) {
		INFO("stopping the server");
		close(_sockfd);
		_started = false;
		return 0;
	} else {
		INFO("could not stop the server, wasn't running");
		return -1;
	}
}

int Server::start()
{
	int 	yes = 1;
	void*	addr;
	char	ipstr[INET6_ADDRSTRLEN];

	_sockfd = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	if (_sockfd < 0) {
		ERROR("could not create server socket");
		return 1;
	}
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		ERROR("can't set socket options");
		return 2;
	}

	if (bind(_sockfd, _servinfo->ai_addr, _servinfo->ai_addrlen) == -1) {
		ERROR("can't bind the socket");
		return 3;
	}
	if (listen(_sockfd, MAX_CONNEXIONS) == -1) {
		ERROR("can't listen to the specified port " + _port);
		exit(6);
	}
	struct sockaddr_in*	ipv4 = (struct sockaddr_in *)_servinfo->ai_addr;
	addr = &(ipv4->sin_addr);
	inet_ntop(_servinfo->ai_family, addr, ipstr, sizeof(ipstr));

	_started = true;

	pollfd server_pfd = {};
	server_pfd.fd = _sockfd;
	server_pfd.events = POLLIN;
	server_pfd.revents = 0;

	_client_pfd_list[_nb_clients++] = server_pfd;
	std::cout << "Server socket " << _sockfd << " added to _client_pfd_list\n";

	std::cout << "Server in now waiting for connections on: ";
	std::cout << ipstr << ":" << _port << std::endl;
	return 0;
}

int Server::handle_recv(int fd, int i)
{
	int ret = _client_list[fd].read_buffer();
	if (ret < 0) {
		ERROR("removing client, having problems reading buffer");
		delete_client(i);
		return -1;
	} else if (ret == 0) {
		while (_client_list[fd].has_message()) {
			const std::string& message = _client_list[fd].extract_message();
			if (!message.empty()) {
				Command command(this, &_client_list[fd], message);
				command.execute_command();
			}
		}
	}
	return 0;
}

int Server::loop()
{
	if (!_started) {
		ERROR("can't loop, server not started");
		return -1;
	}
	int ret_poll = poll(_client_pfd_list, _nb_clients, 200);
	if (ret_poll < 0) {
		ERROR("poll error");
		return 0;
	}
	int listener = _client_pfd_list[0].fd;
	for(int i = 0; i < _nb_clients; i++)
	{
		if (_client_pfd_list[i].revents & POLLIN) {
			int fd = _client_pfd_list[i].fd;
			std::cout << "POLLIN from fd = " << fd << std::endl;
			if (fd == listener) {
				if (create_client() != 0) {
					ERROR("Can't add client");
					return 1;
				}
			} else {
				if (handle_recv(fd, i) != 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int Server::create_client()
{
	Client client;
	struct sockaddr* ptr = (struct sockaddr *)client.get_storage_addr();
	int client_fd = accept(_sockfd, ptr, client.get_addr_len()); 
	if (client_fd == -1) {
		ERROR("accept error, client deleted");
		return 1;
	}

	client.set_fd(client_fd);
	client.set_IP();
	_client_list.insert(std::make_pair(client_fd, client));

	pollfd new_client = {};
	new_client.fd = client_fd;
	new_client.events = POLLIN;
	_client_pfd_list[_nb_clients++] = new_client;

	if (client.get_storage_addr()->ss_family == AF_INET ||
			client.get_storage_addr()->ss_family == AF_INET6) {
		std::cout << "Adding new client fd : " << client.get_fd();
		std::cout << ", IP : " << client.get_IP() << std::endl;
	}
	print_clients();
	return 0;
}

const Client*   Server::get_client(int fd) const
{
	for (int i=0; i < _nb_clients; i++) {
		if (_client_pfd_list[i].fd == fd)
			return &_client_list.at(fd);
	}
	return NULL;
}

Client*   Server::get_client(int fd)
{
	for (int i=0; i < _nb_clients; i++) {
		if (_client_pfd_list[i].fd == fd)
			return &_client_list.at(fd);
	}
	return NULL;
}

const Client* Server::get_client(const std::string& nick) const
{
	for (std::map<int, Client>::const_iterator it = _client_list.begin(); it != _client_list.end(); it++) {
		if (it->second.get_nick() == nick)
			return &it->second;
	}
	return NULL;
}

Client* Server::get_client(const std::string& nick)
{
	for (std::map<int, Client>::iterator it = _client_list.begin(); it != _client_list.end(); it++) {
		if (it->second.get_nick() == nick)
			return &it->second;
	}
	return NULL;
}

const std::string&  Server::get_name() const { return _name; }

const std::string&  Server::get_version() const { return _version; }

void	Server::remove_fd(int start)
{
	for (int i=start + 1; i < _nb_clients; i++) {
		_client_pfd_list[i - 1] = _client_pfd_list[i];
	}
	_nb_clients--;
}

int Server::delete_client(int id)
{
	pollfd* ptr = &_client_pfd_list[id];
	int client_fd = ptr->fd;
	Client* client = get_client(client_fd);
	std::cout << "Removing client fd : " << client_fd; 
	std::cout << ", IP : " << client->get_IP() << std::endl;
	const std::vector<std::string>& channels = client->get_channels();
	for (size_t i=0; i < channels.size(); i++) {
		Channel* channel = get_channel(channels[i]);
		if (channel != NULL)
			channel->quit_user(client, "Connection closed");
	}
	_client_list.erase(client->get_fd());
	remove_fd(id);
	close(client_fd);
	print_clients();
	return 0;
}

void    Server::print_clients()
{
	std::cout << std::endl;
	std::cout << std::setw(25) << std::setfill(' ');
	std::cout << std::string(26, '-') << "\n";
	std::cout << std::setw(25) << std::setfill(' ') << std::left << "|     CLIENT LIST";
	std::cout << "|\n";
	std::cout << std::string(26, '-') << "\n";
	std::cout << std::setw(22) << std::setfill(' ') << std::left << "| Listener : " << _client_pfd_list[0].fd;
	std::cout << "  |\n";
	std::cout << std::string(26, '-') << "\n";
	for (int i = 1; i < _nb_clients; i++) {
		std::cout << std::setw(22) << std::setfill(' ') << std::left << "| Client : " << _client_pfd_list[i].fd;
		std::cout << "  |\n";
		std::cout << std::string(26, '-') << "\n";
	}
	std::cout << std::endl;
}

std::map<int, Client>& 	Server::get_client_list() { return _client_list; }

const std::string& Server::get_password() const { return _password; }

bool    Server::is_valid_port(const std::string& port)
{
	if (port.empty())
		return false;
	for (std::string::const_iterator it = port.begin(); it != port.end(); it++) {
		if (!isdigit(*it))
			return false;
	}
	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535)
		return false;
	return true;
}

bool    Server::is_valid_password(const std::string& password)
{
	if (password.size() < 1 || password.size() > 255)
		return false;
	for (std::string::const_iterator it = password.begin(); it != password.end(); it++) {
		if (std::isspace(*it) || *it == '\0' || *it == ':')
			return false;
	}
	return true;
}

bool    Server::channel_exists(std::string name) { return _channels.find(name) != _channels.end(); }

int Server::create_channel(Client* client, const std::string& name)
{
	Channel channel(client, name);
	if (channel_exists(name)) {
		return -1;
	}
	_channels.insert(std::make_pair(name, channel));
	return 0;
}

Channel*    Server::get_channel(const std::string& name)
{
	try {
		return &_channels.at(name);
	} catch (std::out_of_range& e) {
		return NULL;
	}
}

const Bot*    Server::get_bot(const std::string &name) const {
	for (size_t i = 0; i < _bots.size(); i++) {
		if (_bots[i]->get_name() == name)
			return _bots[i];
	}
	return NULL;
}

bool    Server::nick_already_used(const std::string& nick) const
{
	if (!_client_list.empty()) {
		if (get_client(nick) != NULL)
			return true;
	}
	if (!_bots.empty()) {
		if (get_bot(nick) != NULL)
			return true;
	}
	return false;
}

bool    Server::running() const { return _started; }

void    Server::delete_channel(const std::string& name) { _channels.erase(name); }

std::string  Server::get_date_time() const {
	struct tm  tstruct = {};
	char       buf[80];
	tstruct = *localtime(&_created_at);
	strftime(buf, sizeof(buf), "%X %d/%m/%Y", &tstruct);
	return std::string(buf);
}

std::string Server::get_user_modes() const {
	return "n";
}

std::string Server::get_channel_modes() const {
	return "kilot";
}

void 	Server::write_logo() const
{
	std::string line;
	std::ifstream infile("assets/logo.txt");
	while (std::getline(infile, line))
	{
		std::cout << line << std::endl;
	}	
}
