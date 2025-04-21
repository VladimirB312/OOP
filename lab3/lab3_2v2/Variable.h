#pragma once
#include "Operand.h"
#include "Observable.h"
#include <cmath>

class Variable : public Operand
	, public Observable
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
