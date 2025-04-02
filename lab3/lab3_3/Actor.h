#pragma once
#include "Bank.h"
#include <memory>

class Actor
{
public:
	explicit Actor(Money cash);

	bool GiveMoney(std::unique_ptr<Actor>& actor, Money amount);
	Money GetCash();

protected:
	void RecieveMoney(Money amount);
	Money m_cash;
};