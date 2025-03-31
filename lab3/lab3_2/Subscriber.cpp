#include "Subscriber.h"
#include "Operand.h"

void Subscriber::AddSubscriber(std::shared_ptr<Operand> operand)
{
	m_subsicribers.push_back(operand);
}

void Subscriber::UpdateSubscribers()
{
	for (const auto& sub : m_subsicribers)
	{
		sub->Update();
	}
}
