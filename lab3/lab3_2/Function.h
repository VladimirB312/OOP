#pragma once
#include "Operand.h"

enum class Operation
{
	EMPTY,
	ADDITION,
	MULTIPLICATION,
	SUBTRACTION,
	DIVISION
};

class Function: public Operand
{
public:
	Function(Operand& operand);
	Function(Operand& operandOne, Operand& operandTwo, const Operation& operation);
	double GetValue() override;

private:
	Operand* m_operandOne = nullptr;
	Operand* m_operandTwo = nullptr;
	Operation m_operation = Operation::EMPTY;
	double Calculate();
};