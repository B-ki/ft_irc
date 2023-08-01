#ifndef ROCK_PAPER_SCISSORS_BOT_H
# define ROCK_PAPER_SCISSORS_BOT_H

# include "Bot.h"
# include "error.h"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <unistd.h>
# include <cstdlib>

class RockPaperScissorsBot: public Bot {
public:
	// -- Constructors --
	RockPaperScissorsBot(const std::string& name);
	RockPaperScissorsBot(const RockPaperScissorsBot& bot);

	RockPaperScissorsBot& operator=(const RockPaperScissorsBot& bot);

	// -- Public functions --
	void                reply_to(const Client& client, const std::string& message) const;
	const std::string&  get_name() const;
private:
	// -- Private functions --
	std::string _get_response(const std::string& message) const;
};

#endif
