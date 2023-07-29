#pragma once

#include <iostream>
#include <string>
#include <csignal>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <iomanip>
#include <cstdlib>

#include "Config.h"
#include "color.h"

typedef void (*fun_ptr)(void);
typedef struct timeval t_timeval;

class Test {
	public:

		Test(void);
		Test(std::string name, fun_ptr fun);
		Test(const Test &test);
		Test &operator=(const Test &test);

		~Test(void);

		int			        getPid(void) const;
		int			        getStatus(void) const;
		double		        getTime(void) const;
		const std::string&	getName(void) const;
		fun_ptr		        getFun(void) const;
		bool		        isFailed(void) const;

		bool		exec(const Config& config);
		void		print_trace(void);
		void		print_banner(void) const;

	private:
		int			_pid;
		int			_status;
		int			_exit_code;
		bool		_failed;
		double		_time;
		std::string	_name;
		fun_ptr		_fun;
		int			_stdout;
		int			_stderr;
};

std::string	print_time(double time);
