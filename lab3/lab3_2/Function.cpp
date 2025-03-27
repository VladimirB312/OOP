#include "Function.h"
#include <cmath>
#include <stdexcept>

Function::Function(Operand& operand)
	: m_operandOne(&operand)
{
}

Function::Function(Operand& operandOne, Operand& operandTwo, const Operation& operation)
	: m_operandOne(&operandOne)
	, m_operandTwo(&operandTwo)
	, m_operation(operation)
{
}

double Function::GetValue()
{
	if (std::isnan(m_operandOne->GetValue()))
	{
		return std::nan("");
	}

	if (!m_operandTwo)
	{
		return m_operandOne->GetValue();
	}

	if (std::isnan(m_operandTwo->GetValue()))
	{
		return std::nan("");
	}

	return Calculate();
}

double Function::Calculate()
{
	switch (m_operation)
	{
	case Operation::ADDITION:
		return m_operandOne->GetValue() + m_operandTwo->GetValue();
	case Operation::MULTIPLICATION:
		return m_operandOne->GetValue() * m_operandTwo->GetValue();
	case Operation::SUBTRACTION:
		return m_operandOne->GetValue() - m_operandTwo->GetValue();
	case Operation::DIVISION: {
		if (m_operandTwo->GetValue() == 0.0)
		{
			return std::nan("");
		}

		return m_operandOne->GetValue() - m_operandTwo->GetValue();
	}
	default:
		throw std::runtime_error("Uknown operator");
	}
}
