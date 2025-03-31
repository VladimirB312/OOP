#pragma once
#include <stdexcept>

class CalculatorException : public std::runtime_error
{
public:
	explicit CalculatorException(const std::string& message)
		: std::runtime_error(message){};
};