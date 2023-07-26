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
	tests.push_back(new Test("Parsing 1", &parsing_test_1));
	tests.push_back(new Test("Parsing 2", &parsing_test_2));
	tests.push_back(new Test("Parsing 3", &parsing_test_3));
	tests.push_back(new Test("Parsing 4", &parsing_test_4));
	tests.push_back(new Test("Parsing 5", &parsing_test_5));
	tests.push_back(new Test("Parsing 6", &parsing_test_6));
	tests.push_back(new Test("Parsing 7", &parsing_test_7));
	tests.push_back(new Test("Parsing 8", &parsing_test_8));
	tests.push_back(new Test("Parsing 9", &parsing_test_9));
	tests.push_back(new Test("Parsing 10", &parsing_test_10));
	tests.push_back(new Test("Parsing 11", &parsing_test_11));
	tests.push_back(new Test("Parsing 12", &parsing_test_12));
	tests.push_back(new Test("Parsing 13", &parsing_test_13));
	tests.push_back(new Test("Parsing 14", &parsing_test_14));
	tests.push_back(new Test("Parsing 15", &parsing_test_15));
	tests.push_back(new Test("Parsing 16", &parsing_test_16));
	tests.push_back(new Test("Parsing 17", &parsing_test_17));
	tests.push_back(new Test("Parsing 18", &parsing_test_18));
	//tests.push_back(new Test("Error return", &test_error_function));
	// TODO fix test
    return run_tests(tests, config);
}
