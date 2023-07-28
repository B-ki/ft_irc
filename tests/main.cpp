#include "tests.h"
#include "utils.h"
#include "CmdTest.hpp"

void    fake_test(void)
{
    assert(true);
}

int	main(void)
{
    Config				config;
    std::vector<Test*>	tests;

    config.setStopOnFail(true);
	parsing_test(tests);
	command_test_all(tests);
	// TODO fix test
    return run_tests(tests, config);
}
