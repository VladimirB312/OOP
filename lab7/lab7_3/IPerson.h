#pragma once
#include <string>

// человек
class IPerson
{
public:
	// имя
	virtual std::string GetName() const = 0;
};