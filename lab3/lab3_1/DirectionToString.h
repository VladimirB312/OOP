#pragma once
#include "Car.h"
#include <string>
#include <stdexcept>

std::string DirectionToString(const Car::Direction& direction)
{
	if (direction == Car::Direction::STANDING_STILL)
	{
		return "standing still";
	}

	if (direction == Car::Direction::FORWARD)
	{
		return "forward";
	}

	if (direction == Car::Direction::BACKWARD)
	{
		return "backward";
	}

	throw std::runtime_error("Unknown direction");
}