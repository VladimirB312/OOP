#pragma once
#include "Operand.h"
#include <memory>
#include <vector>

class Subscriber
{
public:
	~Subscriber() = default;
	void AddSubscriber(std::shared_ptr<Operand> operand);
	void UpdateSubscribers();

private:
	std::vector<std::shared_ptr<Operand>> m_subsicribers;
};