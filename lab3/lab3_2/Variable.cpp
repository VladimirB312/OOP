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
}
