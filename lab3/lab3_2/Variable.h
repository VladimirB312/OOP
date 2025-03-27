#pragma once
#include "Operand.h"
#include <cmath>
#include <string>

class Variable : public Operand
{
public:
	Variable() = default;
	Variable(double value);

	const double GetValue() override;
	void SetValue(double value);

private:
	double m_value = std::nan("");
};