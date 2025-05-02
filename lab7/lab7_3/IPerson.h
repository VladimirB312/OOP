#pragma once
#include <string>

// человек
class IPerson
{
public:
	virtual ~IPerson() = default;
	// имя
	virtual std::string GetName() const = 0;
};