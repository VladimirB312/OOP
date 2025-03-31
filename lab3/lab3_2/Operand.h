#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Subscriber.h"

class Operand : public Subscriber
{
public:
	virtual ~Operand() = default;
	virtual double GetValue() = 0;	
	virtual void Update() = 0;	
};