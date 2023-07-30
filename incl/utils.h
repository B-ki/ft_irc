#ifndef UTILS_H
# define UTILS_H

# include <vector>
# include <string>

namespace utils {
	bool is_empty(const char* str);
	std::vector<std::string> split(const std::string& str, const std::string& delim);
}

#endif
