#include <cstring>
#include "tests.h"
#include "CmdTest.hpp"
#include "utils.h"

void    welcome_message()
{
	CmdTest s("5878", "password");
	s.create_client();
	std::string nick = "rmorel";
	s.send(1, "PASS password");
	s.send(1, "NICK " + nick);
	s.send(1, "USER " + nick + " 0 * :Romain Morel");
	std::string expected = "001 rmorel :Welcome to the IRC Network\n";
	expected += "002 rmorel :Your host is ft_irc, running version v1.0\n";
	expected += "003 rmorel :This server was created " + s.get_server().get_date_time() + "\n";
	expected += "004 rmorel ft_irc v1.0 n kilot\n";
	expected += "005 rmorel CHANMODES=kilot CHANTYPES=# :are supported by this server\n";
	expected += "375 rmorel :- ft_irc Message of the day -\n";
	expected += "372 rmorel :Nothing important for now ;(\n";
	expected += "376 rmorel :End of /MOTD command";
	assert_str(s.receive(1), expected);
}

void    not_authenticated()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "NICK rmorel");
	assert_str(s.receive(1), "451 * :You have not registered");
	s.send(1, "JOIN #linux");
	assert_str(s.receive(1), "451 * :You have not registered");
	s.send(1, "PASS password");
	s.send(1, "NICK rmorel");
	s.send(1, "JOIN #linux");
	assert_str(s.receive(1), "451 rmorel :You have not registered");
}

void    invalid_password()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS wrong_password");
	assert_str(s.receive(1), "464 * :Password incorrect");
}

void    pass_not_enough_params()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS");
	assert_str(s.receive(1), "461 * PASS :Not enough parameters");
}

void    password_already_given()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "PASS password");
	assert_str(s.receive(1), "462 * :You may not reregister");
}

void	nick_not_enough_params()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK");
	assert_str(s.receive(1), "431 * :No nickname given");
}

void    invalid_nick()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK #rmorel");
	assert_str(s.receive(1), "432 * #rmorel :Erroneous nickname");
	s.send(1, "NICK rmo:rel");
	assert_str(s.receive(1), "432 * rmo:rel :Erroneous nickname");
}

void    nick_already_in_use()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK rmorel");
	s.send(1, "USER rmorel");
	s.create_client();
	s.send(2, "PASS password");
	s.send(2, "NICK rmorel");
	assert_str(s.receive(2), "433 * rmorel :Nickname is already in use");
}

void    nick_change()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK rmorel");
	s.send(1, "NICK rmorel2");
	assert_str(s.receive(1), ":rmorel!*@127.0.0.1 NICK :rmorel2");
	s.send(1, "USER rmorel 0 * :Romain Morel");
	assert_str(utils::split(s.receive(1), "\n")[0], "001 rmorel2 :Welcome to the IRC Network");
}

void    user_not_enough_params()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER");
	assert_str(s.receive(1), "461 apigeon USER :Not enough parameters");
	s.send(1, "USER arthur");
	assert_str(s.receive(1), "461 apigeon USER :Not enough parameters");
	s.send(1, "USER arthur 0");
	assert_str(s.receive(1), "461 apigeon USER :Not enough parameters");
	s.send(1, "USER arthur 0 *");
	assert_str(s.receive(1), "461 apigeon USER :Not enough parameters");
}

void    user_already_registered()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "USER rmorel 0 * :Romain Morel");
	assert_str(s.receive(1), "462 apigeon :You may not reregister");
}

void    join_not_enough_params()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "JOIN");
	assert_str(s.receive(1), "461 apigeon JOIN :Not enough parameters");
}

void    join_channel()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "JOIN #linux");
	usleep(100000);
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 JOIN :#linux\n353 apigeon = #linux :@apigeon\n366 apigeon #linux :End of /NAMES list");
	s.create_client();
	s.send(2, "PASS password");
	s.send(2, "NICK rmorel");
	s.send(2, "USER romain 0 * :Romain Morel");
	s.receive(2);
	s.send(2, "JOIN #linux");
	usleep(100000);
	assert_str(s.receive(2), ":rmorel!romain@127.0.0.1 JOIN :#linux\n353 rmorel = #linux :@apigeon rmorel\n366 rmorel #linux :End of /NAMES list");
	assert_str(s.receive(1), ":rmorel!romain@127.0.0.1 JOIN :#linux");
}

void    join_invalid_channel() {
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "JOIN linux");
	assert_str(s.receive(1), "476 apigeon linux :Invalid channel name");
	s.send(1, "JOIN #linux&bonjour");
	assert_str(s.receive(1), "476 apigeon #linux&bonjour :Invalid channel name");
	s.send(1, "JOIN #linux;oui");
	assert_str(s.receive(1), "476 apigeon #linux;oui :Invalid channel name");
	s.send(1, "JOIN #l'inux");
	assert_str(s.receive(1), "476 apigeon #l'inux :Invalid channel name");
	s.send(1, "JOIN #[linux]");
	assert_str(s.receive(1), "476 apigeon #[linux] :Invalid channel name");
}

void    join_already_in_channel()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "JOIN #linux");
	s.receive(1);
	s.send(1, "JOIN #linux");
}

void    join_with_topic()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.send(1, "TOPIC #linux :Hello world");
	s.create_client();
	s.send(2, "PASS password");
	s.send(2, "NICK rmorel");
	s.send(2, "USER romain 0 * :Romain Morel");
	s.receive(2);
	s.send(2, "JOIN #linux");
	usleep(100000);
	std::string expected = ":rmorel!romain@127.0.0.1 JOIN :#linux\n";
	expected += "332 rmorel #linux :Hello world\n";
	expected += "333 rmorel #linux apigeon " + s.get_server().get_channel("#linux")->get_topic_set_time() + "\n";
	expected += "353 rmorel = #linux :@apigeon rmorel\n";
	expected += "366 rmorel #linux :End of /NAMES list";
	assert_str(s.receive(2), expected);
}

void    topic_not_enough_params()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.receive(1);
	s.send(1, "TOPIC");
	assert_str(s.receive(1), "461 apigeon TOPIC :Not enough parameters");
}

void    topic_not_in_channel()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.create_client();
	s.send(2, "PASS password");
	s.send(2, "NICK rmorel");
	s.send(2, "USER romain 0 * :Romain Morel");
	s.receive(2);
	s.send(2, "TOPIC #linux");
	assert_str(s.receive(2), "442 rmorel #linux :You're not on that channel");
	s.send(2, "TOPIC #linux :Boom le topic de fou");
	assert_str(s.receive(2), "442 rmorel #linux :You're not on that channel");
}

void    topic_no_such_channel()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.receive(1);
	s.send(1, "TOPIC #linux");
	assert_str(s.receive(1), "403 apigeon #linux :No such channel");
	s.send(1, "TOPIC #linux :Boom le topic de fou");
	assert_str(s.receive(1), "403 apigeon #linux :No such channel");
}

void    topic_get_info()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.receive(1);
	s.send(1, "TOPIC #linux");
	assert_str(s.receive(1), "331 apigeon #linux :No topic is set");
	s.send(1, "TOPIC #linux :Boom le topic de fou");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 TOPIC #linux :Boom le topic de fou");
	s.send(1, "TOPIC #linux");
	usleep(100000);
	assert_str(s.receive(1), "332 apigeon #linux :Boom le topic de fou\n333 apigeon #linux apigeon " + s.get_server().get_channel("#linux")->get_topic_set_time());
	s.send(1, "TOPIC #linux :");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 TOPIC #linux :");
	s.send(1, "TOPIC #linux");
	assert_str(s.receive(1), "331 apigeon #linux :No topic is set");
}

void    topic_change_no_privileges()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.create_client();
	s.send(2, "PASS password");
	s.send(2, "NICK rmorel");
	s.send(2, "USER romain 0 * :Romain Morel");
	s.send(2, "JOIN #linux");
	s.receive(2);
	s.send(2, "TOPIC #linux :Boom le topic de fou");
	assert_str(s.receive(2), "482 rmorel #linux :You're not channel operator");
}

void 	mode_invite()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.receive(1);
	s.send(1, "MODE #linux +i");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 MODE #linux +i");
	s.send(1, "MODE #linux -i");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 MODE #linux -i");
}

void 	mode_topic()
{
	CmdTest s("5878", "password");
	s.create_client();
	s.send(1, "PASS password");
	s.send(1, "NICK apigeon");
	s.send(1, "USER arthur 0 * :Arthur Pigeon");
	s.send(1, "JOIN #linux");
	s.receive(1);
	s.send(1, "MODE #linux +t");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 MODE #linux +t");
	s.send(1, "MODE #linux -t");
	assert_str(s.receive(1), ":apigeon!arthur@127.0.0.1 MODE #linux -t");
}

void command_test_all(std::vector<Test*>& tests)
{
	tests.push_back(new Test("command::welcome_message", &welcome_message));
	tests.push_back(new Test("command::not_authenticated", &not_authenticated));
	tests.push_back(new Test("command::PASS::invalid_password", &invalid_password));
	tests.push_back(new Test("command::PASS::not_enough_params", &pass_not_enough_params));
	tests.push_back(new Test("command::PASS::password_already_given", &password_already_given));
	tests.push_back(new Test("command::NICK::not_enough_params", &nick_not_enough_params));
	tests.push_back(new Test("command::NICK::invalid_nick", &invalid_nick));
	tests.push_back(new Test("command::NICK::nick_already_in_use", &nick_already_in_use));
	tests.push_back(new Test("command::NICK::nick_change", &nick_change));
	tests.push_back(new Test("command::USER::not_enough_params", &user_not_enough_params));
	tests.push_back(new Test("command::USER::already_registered", &user_already_registered));
	tests.push_back(new Test("command::JOIN::not_enough_params", &join_not_enough_params));
	tests.push_back(new Test("command::JOIN::channel", &join_channel));
	tests.push_back(new Test("command::JOIN::invalid_channel", &join_invalid_channel));
	tests.push_back(new Test("command::JOIN::already_in_channel", &join_already_in_channel));
	tests.push_back(new Test("command::JOIN::with_topic", &join_with_topic));
	// TODO tests for JOIN on invite only and with password. And for JOIN of multiple channels
	tests.push_back(new Test("command::TOPIC::not_enough_params", &topic_not_enough_params));
	tests.push_back(new Test("command::TOPIC::not_in_channel", &topic_not_in_channel));
	tests.push_back(new Test("command::TOPIC::no_such_channel", &topic_no_such_channel));
	tests.push_back(new Test("command::TOPIC::get_info", &topic_get_info));
	tests.push_back(new Test("command::TOPIC::change_no_privileges", &topic_change_no_privileges));
	tests.push_back(new Test("command::MODE::invite", &mode_invite));
	tests.push_back(new Test("command::MODE::topic", &mode_topic));
	// TODO tests for INVITE, PART, KICK
}
