#include "Test.h"

Test::Test(void)
{
	_name = "";
	_fun = NULL;
	_pid = 0;
	_status = 0;
	_time = 0;
	_failed = false;
	_stdout = 1;
	_stderr = 2;
}

Test::Test(std::string name, fun_ptr fun)
{
	_name = name;
	_fun = fun;
	_pid = 0;
	_status = 0;
	_time = 0;
	_failed = false;
	_stdout = 1;
	_stderr = 2;
}

Test::Test(const Test& test)
{
	*this = test;
}

Test& Test::operator=(const Test& test)
{
	if (this != &test) {
		_name = test._name;
		_fun = test._fun;
		_pid = test._pid;
		_status = test._status;
		_time = test._time;
		_failed = test._failed;
		_stdout = test._stdout;
		_stderr = test._stderr;
	}
	return *this;
}

Test::~Test(void)
{
	if (_stdout != STDOUT_FILENO)
		close(_stdout);
	if (_stderr != STDERR_FILENO)
		close(_stderr);
}


int			Test::getPid(void) const
{
	return _pid;
}

int			Test::getStatus(void) const
{
	return _status;
}

double		Test::getTime(void) const
{
	return _time;
}

const std::string&	Test::getName(void) const
{
	return _name;
}

fun_ptr		Test::getFun(void) const
{
	return _fun;
}

bool		Test::isFailed(void) const
{
	return _failed;
}

static double	timediff(t_timeval end, t_timeval start)
{
	double	diff;

	diff = ((end.tv_sec - start.tv_sec) * 1000 + ((double)(end.tv_usec - start.tv_usec)) / 1000);
	return (diff / 1000);
}

void	Test::print_banner(void) const
{
	std::string	state;

	if (_exit_code == 0)
		state = T_GREEN "PASS" T_RESET;
	else
		state = T_RED "FAIL" T_RESET;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "        " << state << " [" << print_time(_time) << "s]        " << T_BLUE + _name + T_RESET;
	if (WIFSIGNALED(_status)) {
		std::string	sig;
		if (_exit_code == SIGSEGV)
			sig = "SIGSEGV";
		else if (_exit_code == SIGABRT)
			sig = "SIGABRT";
		else if (_exit_code == SIGBUS)
			sig = "SIGBUS";
		else if (_exit_code == SIGPIPE)
			sig = "SIGPIPE";
		else if (_exit_code == SIGUSR1)
			sig = "TIMEOUT";
		else
			sig = "";
		std::cout << " " T_RED << sig << T_RESET;
	}
	std::cout << std::endl;
}

static void	print_pipe(int fd)
{
	int		ret;
	char	buf[512 + 1];

	do {
		ret = read(fd, buf, 512);
		buf[ret] = 0;
		std::cout << buf;
	} while (ret != 0);
}

void	Test::print_trace(void)
{
	if (_stdout == STDOUT_FILENO || _stderr == STDERR_FILENO)
		return ;

	print_banner();

	if (_failed) {
		std::cout << "\n" T_RED "--- STDOUT:" T_RESET "           \t\t" T_BLUE << _name << T_RESET " " T_RED "---" T_RESET "\n";
		print_pipe(_stdout);
		std::cout << "\n" T_RED "--- STDERR:" T_RESET "           \t\t" T_BLUE << _name << T_RESET " " T_RED "---" T_RESET "\n";
		print_pipe(_stderr);
		std::cout << "\n" T_RED "---" T_RESET "\n";
	}

	close(_stderr);
	close(_stdout);
	_stdout = STDOUT_FILENO;
	_stderr = STDERR_FILENO;
}

static int	settimeout(int pid, uint timeout)
{
	int	pid2;

	pid2 = fork();
	if (pid2 == 0) {
		usleep(timeout * 1000);
		kill(pid, SIGUSR1);
		exit(0);
	}
	return (pid2);
}

bool	Test::exec(const Config& config)
{
	int			timeout_pid;
	int			fd_out[2], fd_err[2];
	t_timeval	start, end;

	if (pipe(fd_out) == -1) return (false);
	if (pipe(fd_err) == -1) return (false);
	gettimeofday(&start, NULL);
	_pid = fork();
	if (_pid == -1) return (false);
	if (_pid == 0) {
		close(fd_out[0]);
		close(fd_err[0]);
		dup2(fd_out[1], STDOUT_FILENO);
		dup2(fd_err[1], STDERR_FILENO);
		_fun();
		exit(0);
	}
	_stdout = fd_out[0];
	_stderr = fd_err[0];
	close(fd_out[1]);
	close(fd_err[1]);
	timeout_pid = settimeout(_pid, config.getTimeout());
	waitpid(_pid, &_status, 0);
	gettimeofday(&end, NULL);
	kill(timeout_pid, SIGKILL);
	waitpid(timeout_pid, NULL, 0);
	_time = timediff(end, start);
	if (WIFEXITED(_status))
		_exit_code = WEXITSTATUS(_status);
	else if (WIFSIGNALED(_status))
		_exit_code = WTERMSIG(_status);
	else
		_exit_code = -1;
	if (_exit_code != 0)
		_failed = true;
	print_trace();
	return (true);
}

std::string	print_time(double time)
{
	if (time >= 100) {
		std::cout << " >=100";
		return "";
	}
	std::cout << std::fixed << std::setprecision(3);
	if (time < 10)
		std::cout << " ";
	std::cout << time;
	return "";
}
