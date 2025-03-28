#pragma once
#include <stdexcept>

class ParserException : public std::runtime_error
{
public:
	explicit ParserException(const std::string& message)
		: std::runtime_error(message){};
};