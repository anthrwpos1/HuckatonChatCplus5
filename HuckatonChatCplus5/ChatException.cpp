#include "ChatException.h"

ChatException::ChatException(std::string description) : exception(description.c_str())
{
}

char const * ChatException::what() const
{
	return exception::what();
}
