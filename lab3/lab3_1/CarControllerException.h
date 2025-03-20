#pragma once
#include <stdexcept>

class CarControllerError : public std::runtime_error
{
public:
	explicit CarControllerError(const std::string& message)
		: std::runtime_error(message.c_str()){};
};