#pragma once
#include <memory>
#include <string>
#include <vector>

class Operand
{
public:
	virtual ~Operand() = default;
	virtual double GetValue() = 0;	
	virtual void AddSubscriber(std::shared_ptr<Operand> operand) = 0;
	virtual void Update() = 0;	
};