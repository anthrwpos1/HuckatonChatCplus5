#include "ChatException.h"

ChatException::ChatException(std::string description) : runtime_error(description.c_str())
{
}

char const * ChatException::what() const noexcept
{
	return runtime_error::what();
}
