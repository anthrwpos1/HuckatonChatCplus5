#pragma once
#include <exception>
#include <string>

class CLIException : public std::exception
{
public:
	CLIException(std::string description);
	char const* what() const override;
};