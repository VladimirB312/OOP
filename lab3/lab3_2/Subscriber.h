#pragma once
#include <vector>
#include <memory>

class Operand;

class Subscriber
{
public:
	~Subscriber() = default;
	void AddSubscriber(std::shared_ptr<Operand> operand);
	void UpdateSubscribers();

private:
	std::vector<std::shared_ptr<Operand>> m_subsicribers;
};