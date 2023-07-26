#include <ctype.h>
#include <unistd.h>

bool    is_empty(const char* str)
{
	if (str == NULL)
		return true;
	while (*str)
	{
		if (!isspace(*str))
			return false;
		str++;
	}
	return true;
}
