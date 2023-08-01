#ifndef BOT_H
#define BOT_H

# include "Client.h"
# include <string>

class Bot {
public:
	virtual ~Bot() {};
	// -- Public functions --
	virtual void                reply_to(const Client& client, const std::string& message) const = 0;
	virtual const std::string&  get_name() const = 0;

protected:
	// -- Protected attributes --
	std::string _name;
};


#endif
