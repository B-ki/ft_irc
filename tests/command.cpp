#include <cstring>
#include "tests.h"
#include "CmdTest.hpp"

void welcome_message()
{
	CmdTest cmd_test("5878", "password");
	std::string nick = "rmorel";
	cmd_test.send("PASS password");
	cmd_test.send("NICK " + nick);
	cmd_test.send("USER " + nick);
	assert_str(cmd_test.receive(), "001 " + nick + " :Welcome to the IRC Network");
	cmd_test.stop();
}

void command_test_all(std::vector<Test*>& tests)
{
	tests.push_back(new Test("command::welcome_message", &welcome_message));
}
