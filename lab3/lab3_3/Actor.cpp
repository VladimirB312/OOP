#include "Actor.h"

Actor::Actor(Money cash)
	: m_cash(cash)
{
}


bool Actor::GiveMoney(std::unique_ptr<Actor>& actor, Money amount)
{
	if (m_cash < amount || amount < 0)
	{
		return false; 
	}

	actor->RecieveMoney(amount);
	m_cash -= amount;

	return true;
}

void Actor::RecieveMoney(Money amount)
{
	m_cash += amount;
}

Money Actor::GetCash()
{
	return m_cash;
}