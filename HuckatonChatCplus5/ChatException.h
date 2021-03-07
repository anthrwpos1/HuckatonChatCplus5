#pragma once
#include <exception>
#include <string>

class ChatException : public std::exception
{
public:
	ChatException(std::string description);
	char const* what() const override;
};