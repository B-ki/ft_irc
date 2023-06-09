#include "error.h"

void	log(e_log_type type, std::string msg, std::string file, int line)
{
	switch (type) {
    	case LOG_INFO:
			std::cerr << "[" << GREEN  << "INFO ";
			break;
		case LOG_DEBUG:
			std::cerr << "[" << BLUE  << "DEBUG ";
			break;
		case LOG_WARNING:
			std::cerr << "[" << YELLOW  << "WARNING ";
			break;
		case LOG_ERROR:
			std::cerr << "[" << RED  << "ERROR ";
			break;
    }
	std::cerr << RESET << file << ":" << line << "] " << msg << std::endl;
}
