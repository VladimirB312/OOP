#pragma once
#include <stdexcept>

class CalculatorUIException : public std::runtime_error
{
public:
	explicit CalculatorUIException(const std::string& message)
		: std::runtime_error(message){};
};