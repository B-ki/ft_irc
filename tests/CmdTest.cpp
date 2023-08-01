#include "CmdTest.hpp"
#include <pthread.h>
#include <errno.h>

static void*    start_server_loop(void* ptr)
{
	Server* server = (Server*)ptr;
	while (server->running())
		server->loop();
	return NULL;
}

CmdTest::CmdTest(const std::string& port, const std::string& password) : _server(port, password), _port(port), _clients_fd()
{
	_server.start();
	pthread_create(&_server_thread_id, NULL, &start_server_loop, (void*)&_server);
}

CmdTest::~CmdTest() { stop(); }

void    CmdTest::create_client() {
	int client_fd;
	struct sockaddr_in serv_addr;
	struct timeval tv;

	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		ERROR("Socket creation error");
		exit(1);
	}
	tv.tv_sec = 0;
	tv.tv_usec = 200000;
	setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(_port.c_str()));
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		ERROR("Invalid address/ Address not supported");
		exit(1);
	}
	if (connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		ERROR("Connection Failed");
		exit(1);
	}
	_clients_fd.push_back(client_fd);
}

const std::string CmdTest::receive(size_t id)
{
	if (id < 1 || id > _clients_fd.size()) {
		ERROR("invalid client id");
		exit(1);
	}
	id--;
	char _buf[1024 + 1] = {0};
	usleep(5000); // To be sure the server have time to send the message
	ssize_t num_bytes = recv(_clients_fd[id], _buf, sizeof(_buf), 0);
	if (num_bytes <= 0 && errno != EAGAIN) {
		ERROR(std::string("Cannot read from server: ") + strerror(errno));
		exit(1);
	}
	_buf[num_bytes] = '\0';
	if (_buf[num_bytes - 1] == '\n')
		_buf[num_bytes - 1] = '\0';
	return std::string(_buf);
}

void CmdTest::send(size_t id, const std::string& tested)
{
	if (id < 1 || id > _clients_fd.size()) {
		ERROR("invalid client id");
		exit(1);
	}
	id--;
	INFO( "Tested string is : " << tested);
	if (::send(_clients_fd[id], (tested + '\n').c_str(), tested.size() + 1, 0) == -1) {
		ERROR("cannot send message to server");
		exit(1);
	}
}

void CmdTest::stop()
{
	for (size_t i = 0; i < _clients_fd.size(); i++)
		close(_clients_fd[i]);
	_server.stop();
	pthread_join(_server_thread_id, NULL);
}

Server& CmdTest::get_server() { return _server; }
