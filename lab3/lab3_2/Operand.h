#pragma once
#include <string>

class Operand
{
public:
	virtual double GetValue() = 0;
	virtual ~Operand() = default;
};