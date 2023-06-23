#ifndef ERROR_H
# define ERROR_H

#include <iostream>
#include <string>
#include "color.h"

typedef enum	e_log_type
{
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR
}				t_log_type;

void	log(e_log_type type, std::string msg, std::string function, int line);

# define INFO(msg) LOG(LOG_INFO, msg)
# define DEBUG(msg) LOG(LOG_DEBUG, msg)
# define WARNING(msg) LOG(LOG_WARNING, msg)
# define ERROR(msg) LOG(LOG_ERROR, msg)

# ifdef DEBUG_MODE
#  define LOG(type, msg) (log(type, msg, __FILE__, __LINE__))
# else
#  define LOG(type, msg) (NULL)
# endif


#endif
