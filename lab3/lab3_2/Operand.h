#pragma once
#include <memory>
#include <string>
#include <vector>

class Operand
{
public:
	virtual double GetValue() = 0;
	virtual ~Operand() = default;
	virtual void AddSubscriber(std::shared_ptr<Operand> operand) = 0;
	virtual void Update() = 0;
	virtual void UpdateSubscribers() = 0;	
};