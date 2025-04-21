#include "Observable.h"
#include "Operand.h"

void Observable::AddSubscriber(std::shared_ptr<Operand> operand)
{
	m_subsicribers.push_back(operand);
}

void Observable::UpdateSubscribers()
{
	for (const auto& sub : m_subsicribers)
	{
		sub->Update();
	}
}
