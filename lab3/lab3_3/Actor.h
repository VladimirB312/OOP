#pragma once
#include "Bank.h"
#include <memory>

class Actor
{
public:
	explicit Actor(Money cash);

	bool GiveMoney(Actor& actor, Money amount);
	Money GetCash();
	virtual ~Actor() = default;

protected:
	Money m_cash;
	std::string m_name;

private:
	void RecieveMoney(Money amount);
};