#pragma once

#include <iostream>
#include <unistd.h>
#include <csignal>
#include <sys/time.h>
#include <vector>
#include <string>
#include <string.h>
#include <cassert>

#include "core/Test.h"
#include "core/Config.h"
#include "parsing/Message.h"
#include "constant.h"
#include "command/Command.h"
#include "command/error_command.h"

void 	__assert_str(const std::string& s1, const std::string& s2, const char *file,
                         const char *function, int line);

#define assert_str(s1, s2) __assert_str(s1, s2, __FILE__, __func__, __LINE__)

int   	run_tests(std::vector<Test*> tests, Config& config);

void  	parsing_all_test(void);
void 	test_error_function();

void 	parsing_test_cmd(cmd_type expected_cmd, 
			std::vector<std::string> expected_params,
			std::map<std::string, std::string> expected_tags,
			std::string expected_prefix,
			Message &message);
void 	parsing_test(std::vector<Test*>& tests);
void 	command_test_all(std::vector<Test*>& tests);
