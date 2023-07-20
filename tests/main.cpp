#include "tests.h"
#include "utils.h"

void    fake_test(void)
{
    assert(true);
}

int	main(void)
{
    Config				config;
    std::vector<Test*>	tests;

    config.setStopOnFail(true);
    tests.push_back(new Test("fake_test", &fake_test));
	tests.push_back(new Test("Parsing test", &parsing_all_test));
	tests.push_back(new Test("Error return", &parsing_all_test));
    return run_tests(tests, config);
}
