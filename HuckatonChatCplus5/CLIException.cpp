#include "CLIException.h"

CLIException::CLIException(std::string description) : exception(description.c_str())
{
}

char const * CLIException::what() const
{
	return exception::what();
}
