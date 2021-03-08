#include "CLIException.h"

CLIException::CLIException(std::string description) : runtime_error(description.c_str())
{
}

char const * CLIException::what() const noexcept
{
	return runtime_error::what();
}
