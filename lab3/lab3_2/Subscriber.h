#pragma once
#include "Operand.h"

class Subscriber
{
public:
	void AddSubscriber(std::shared_ptr<Operand> operand);
	void UpdateSubscribers();

private:
	std::vector<std::shared_ptr<Operand>> m_subsicribers;
};