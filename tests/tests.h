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

#define assert_str(s1, s2) \
    (strcmp(s1, s2) != 0 ? \
    __assert_str_rtn(s1, s2, __FILE__, __func__, __LINE__) : \
    (void)0)

int   	run_tests(std::vector<Test*> tests, Config& config);
void  	parsing_all_test(void);
void 	test_error_function();
void 	__assert_str_rtn(const char *s1, const char *s2, const char *file,
                        const char *function, int line);
void 	parsing_test_cmd(cmd_type expected_cmd, 
			std::vector<std::string> expected_params,
			std::map<std::string, std::string> expected_tags,
			std::string expected_prefix,
			Message &message);
void 	parsing_test_1(void);
void 	parsing_test_2(void);
void 	parsing_test_3(void);
void 	parsing_test_4(void);
void 	parsing_test_5(void);
void 	parsing_test_6(void);
void 	parsing_test_7(void);
void 	parsing_test_8(void);
void 	parsing_test_9(void);
void 	parsing_test_10(void);
void 	parsing_test_11(void);
void 	parsing_test_12(void);
void 	parsing_test_13(void);
void 	parsing_test_14(void);
void 	parsing_test_15(void);
void 	parsing_test_16(void);
void 	parsing_test_17(void);
void 	parsing_test_18(void);
