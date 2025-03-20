#pragma once
#include <stdexcept>

class CarError : public std::runtime_error
{
public:
	explicit CarError(const std::string& message)
		: std::runtime_error(message.c_str()){};
};

class GearError : public CarError
{
public:
	explicit GearError(const std::string& message)
		: CarError(message){};
};

class SpeedError : public CarError
{
public:
	explicit SpeedError(const std::string& message)
		: CarError(message){};
};