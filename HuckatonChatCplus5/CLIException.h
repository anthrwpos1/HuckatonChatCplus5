#pragma once

#include <string>
#include <stdexcept>
class CLIException : public std::runtime_error
{
public:
	CLIException(std::string description);
	char const* what() const noexcept override;
};