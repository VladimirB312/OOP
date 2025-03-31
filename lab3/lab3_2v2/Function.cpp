#include "Function.h"
#include <cmath>
#include <stdexcept>

Function::Function(std::shared_ptr<Operand> operand)
	: m_operandOne(operand)
{
	SetValue();
}

Function::Function(std::shared_ptr<Operand> operandOne, std::shared_ptr<Operand> operandTwo, const Operation& operation)
	: m_operandOne(operandOne)
	, m_operandTwo(operandTwo)
	, m_operation(operation)
{
	SetValue();
}

void Function::Subscribe()
{
	if (auto subOne = std::dynamic_pointer_cast<Subscriber>(m_operandOne))
	{
		subOne->AddSubscriber(shared_from_this());
	}

	if (auto subTwo = std::dynamic_pointer_cast<Subscriber>(m_operandTwo))
	{
		subTwo->AddSubscriber(shared_from_this());
	}

	m_isSubscribed = true;
}

double Function::GetValue()
{
	if (!m_isSubscribed)
	{
		SetValue();
	}

	return m_value;
}

void Function::SetValue()
{
	if (!m_operandTwo)
	{
		m_value = m_operandOne->GetValue();
		return;
	}

	if (std::isnan(m_operandTwo->GetValue()) || std::isnan(m_operandOne->GetValue()))
	{
		m_value = std::nan("");
		return;
	}

	m_value = Calculate();
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

		return m_operandOne->GetValue() / m_operandTwo->GetValue();
	}
	default:
		throw std::runtime_error("Uknown operator");
	}
}

void Function::Update()
{
	SetValue();
	UpdateSubscribers();
}
