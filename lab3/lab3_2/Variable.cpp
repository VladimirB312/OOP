#include "Variable.h"

Variable::Variable(double value)
	: m_value(value)
{
}

double Variable::GetValue()
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
	UpdateSubscribers();
}

void Variable::AddSubscriber(std::shared_ptr<Operand> operand)
{
	m_subsicribers.push_back(operand);
}

void Variable::UpdateSubscribers()
{
	for (const auto& sub : m_subsicribers)
	{
		sub->Update();
	}
}

void Variable::Update()
{
}