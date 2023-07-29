#include "core/Test.h"
#include "tests.h"

void 	__assert_str(const std::string& s1, const std::string& s2, const char *file, const char *function, int line)
{
	if (s1 != s2) {
		std::cerr << "Assertion failed: (\"" << s1 << "\" != \"" << s2 << "\"), function ";
		std::cerr << function << ", file" << file << ", line" << line << ".\n";
		exit(2);
	}
}

bool	launch_test(Test* test, Config& config)
{
	return (test->exec(config));
}

int	run_tests(std::vector<Test*> tests, Config& config)
{
	uint		i, failed, ret;
	double		total_time;
	Test*		test;

	i = failed = total_time = ret = 0;
	std::cout << "    " T_GREEN "Starting" T_RESET " " << tests.size() << " tests\n";
	std::cout << "------------\n";
	std::vector<Test*>::iterator it = tests.begin();
	test = NULL;
	for (; it != tests.end(); it++) {
		i++;
		test = *it;
		launch_test(test, config);
		failed += test->isFailed();
		total_time += test->getTime();
		if (config.doStopOnFail() && test->isFailed()) break;
	}
	if (config.doStopOnFail() && it != tests.end() && test && test->isFailed())
		std::cout << T_RED "Canceling due to test failure" T_RESET "\n";
	std::cout << "------------\n";
	std::cout << "     " T_GREEN "Summary" T_RESET " [";
	std::cout << print_time(test->getTime()) << "s]" << " " << i << "/";
	std::cout << tests.size() << " tests run: " << i - failed;
	std::cout << " " T_GREEN "passed" T_RESET ", " << failed << " " T_RED "failed" T_RESET "\n";
	it = tests.begin();
  if (failed)
    ret = 1;
	for (; it != tests.end(); it++) {
		test = *it;
		if (test->isFailed())
			test->print_banner();
		delete test;
	}
  return ret;
}
