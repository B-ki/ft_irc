#include "CmdTest.hpp"
#include <pthread.h>

static void*    start_server_loop(void* ptr)
{
	Server* server = (Server*)ptr;
	while (server->_started)
		server->loop();
	return NULL;
}

CmdTest::CmdTest(const std::string& port, const std::string& password) : _server(port, password), _client_fd(-1)
{
	_server.start();
	pthread_create(&_server_thread_id, NULL, &start_server_loop, (void*)&_server);
	struct sockaddr_in serv_addr;
	if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		ERROR("Socket creation error");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(port.c_str()));
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		ERROR("Invalid address/ Address not supported");
		exit(1);
	}
	if (connect(_client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		ERROR("Connection Failed");
		exit(1);
	}
}

CmdTest::~CmdTest() { stop(); }

const std::string CmdTest::receive()
{
	char _buf[1024] = {0};
	ssize_t num_bytes = ::read(_client_fd, _buf, sizeof(_buf));
	if (num_bytes <= 0) {
		ERROR("cannot read message from server");
		exit(1);
	}
	_buf[num_bytes] = '\0';
	if (_buf[num_bytes - 1] == '\n')
		_buf[num_bytes - 1] = '\0';
	return std::string(_buf);
}

void CmdTest::send(const std::string& tested)
{
	INFO( "Tested string is : " << tested);
	if (::send(_client_fd, (tested + '\n').c_str(), tested.size() + 1, 0) == -1) {
		ERROR("cannot send message to server");
		exit(1);
	}
}

void CmdTest::stop()
{
	close(_client_fd);
	_server.stop();
	pthread_join(_server_thread_id, NULL);
}
