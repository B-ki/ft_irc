#include "server/RockPaperScissorsBot.h"

RockPaperScissorsBot::RockPaperScissorsBot(const std::string& name) { _name = name; }

RockPaperScissorsBot::RockPaperScissorsBot(const RockPaperScissorsBot& bot) { *this = bot; }

RockPaperScissorsBot& RockPaperScissorsBot::operator=(const RockPaperScissorsBot& bot)
{
	if (this != &bot)
		_name = bot._name;
	return *this;
}

void    RockPaperScissorsBot::reply_to(const Client& client, const std::string& message) const
{
	const std::string    response = _get_response(message);
	client.send(":" + _name + " NOTICE " + client.get_nick() + " :" + response + "\n");
}

const std::string&  RockPaperScissorsBot::get_name() const { return _name; }

std::string   RockPaperScissorsBot::_get_response(const std::string &message) const {
	if (message != "rock" && message != "paper" && message != "scissors")
		return "Please give me a valid command in order to play: <rock|paper|scissors>";
	std::string   choices[3] = {"rock", "paper", "scissors"};
	std::string   bot_choice = choices[rand() % 3];
	if (message == bot_choice)
		return "I chose " + bot_choice + " too! It's a tie!";
	if (message == "rock" && bot_choice == "paper")
		return "I chose paper! I win!";
	if (message == "rock" && bot_choice == "scissors")
		return "I chose scissors! You win!";
	if (message == "paper" && bot_choice == "rock")
		return "I chose rock! You win!";
	if (message == "paper" && bot_choice == "scissors")
		return "I chose scissors! I win!";
	if (message == "scissors" && bot_choice == "rock")
		return "I chose rock! I win!";
	if (message == "scissors" && bot_choice == "paper")
		return "I chose paper! You win!";
	return "Something went wrong!";
}
