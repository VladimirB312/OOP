#pragma once
#include "Operand.h"
#include <cmath>

enum class Operation
{
	ADDITION,
	MULTIPLICATION,
	SUBTRACTION,
	DIVISION
};

class Function : public Operand
	, public std::enable_shared_from_this<Function>
{
public:
	Function(std::shared_ptr<Operand> operand);
	Function(std::shared_ptr<Operand> operandOne, std::shared_ptr<Operand> operandTwo, const Operation& operation);
	double GetValue() override;
	void SetValue();
	void Subscribe();
	void Update() override;

private:
	double m_value;
	bool m_isSubscribed = false;
	std::shared_ptr<Operand> m_operandOne = nullptr;
	std::shared_ptr<Operand> m_operandTwo = nullptr;
	Operation m_operation;
	double Calculate();
};