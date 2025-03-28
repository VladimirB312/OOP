#pragma once
#include "Operand.h"
#include <cmath>
#include <memory>

enum class Operation
{
	ADDITION,
	MULTIPLICATION,
	SUBTRACTION,
	DIVISION
};

class Function : public Operand
{
public:
	Function(std::shared_ptr<Operand> operand);
	Function(std::shared_ptr<Operand> operandOne, std::shared_ptr<Operand> operandTwo, const Operation& operation);
	double GetValue() override;

private:
	std::shared_ptr<Operand> m_operandOne = nullptr;
	std::shared_ptr<Operand> m_operandTwo = nullptr;
	Operation m_operation;
	double Calculate();
};