#pragma once
#include <string>
#include <stdexcept>

class ChatException : public std::runtime_error
{
public:
	ChatException(std::string description);
	char const* what() const noexcept override;
};