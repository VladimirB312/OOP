#pragma once
#include "Operand.h"
#include <cmath>

class Variable : public Operand
{
public:
	Variable() = default;
	Variable(double value);
	double GetValue() override;
	void SetValue(double value);
	void Update() override;

private:
	double m_value = std::nan("");
};
