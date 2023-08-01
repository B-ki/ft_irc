#ifndef STRUCT_H
# define STRUCT_H

#include <string>
#include <vector>

struct ModeReply {
	bool t_is_set;
	bool i_is_set;
	bool l_is_set;
	bool k_is_set;
	bool o_is_set;
	std::string modestring;
	std::vector<std::string> args;

	ModeReply();
};

#endif
