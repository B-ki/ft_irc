#include "tests.h"
#include "utils.h"

void    fake_test(void)
{
    assert(true);
}

void    test_min(void)
{
    assert(utils::min(1, 2) == 1);
    assert(utils::min(2, 1) == 1);
    assert(utils::min(10, 10) == 10);
}

void test_bki(void)
{
	assert(strcmp("ab", "abcd") == 0);
}

int	main(void)
{
    Config				config;
    std::vector<Test*>	tests;

    config.setStopOnFail(true);
    tests.push_back(new Test("fake_test", &fake_test));
    tests.push_back(new Test("utils::min", &test_min));
    tests.push_back(new Test("test_bki", &test_bki));
    run_tests(tests, config);
    return (0);
}
