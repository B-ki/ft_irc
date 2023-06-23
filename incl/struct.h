#ifndef STRUCT_H
# define STRUCT_H

# include "constant.h"
# include <string>
# include <map>
# include <vector>

typedef struct s_client
{
}	t_client;

typedef struct s_message 
{
	std::map<std::string, std::string> 	tags;
	std::string 						source;
	t_cmd_type 							cmd;
	std::vector<std::string> 			parameters;
}	t_message;

#endif
