#include "core/Test.h"
#include "tests.h"

void	__assert_str_rtn(std::string s1, std::string s2, std::string file, std::string function, int line)
{
	std::cerr << "Assertion failed: (\"" << s1 << "\" != \"" << s2 << "\"), function ";
	std::cerr << function << ", file" << file << ", line" << line << ".\n";
	exit(2);
}

bool	launch_test(Test* test, Config& config)
{
	return (test->exec(config));
}

void	run_tests(std::vector<Test*> tests, Config& config)
{
	uint		i, failed;
	double		total_time;
	Test*		test;

	i = failed = total_time = 0;
	std::cout << "    " GREEN "Starting" RESET " " << tests.size() << " tests\n";
	std::cout << "------------\n";
	std::vector<Test*>::iterator it = tests.begin();
	test = NULL;
	for (; it != tests.end(); it++) {
		test = *it;
		launch_test(test, config);
		failed += test->isFailed();
		total_time += test->getTime();
		if (config.doStopOnFail() && test->isFailed()) break;
	}
	if (config.doStopOnFail() && it != tests.end() && test && test->isFailed())
		std::cout << RED "Canceling due to test failure" RESET "\n";
	std::cout << "------------\n";
	i = (it - tests.begin()) + 1;
	std::cout << "     " GREEN "Summary" RESET " [";
	std::cout << print_time(test->getTime()) << "s]" << " " << i << "/";
	std::cout << tests.size() << " tests run: " << i - failed;
	std::cout << " " GREEN "passed" RESET ", " << failed << " " RED "failed" RESET "\n";
	it = tests.begin();
	for (; it != tests.end(); it++) {
		test = *it;
		if (test->isFailed())
			test->print_banner();
		delete test;
	}
}
