#pragma once
#include "Actor.h"

class ActorWithCard: public Actor
{
public:
	ActorWithCard(Bank& bank, Money cash);
	void SendMoney(std::unique_ptr<ActorWithCard>& actor, Money amount);
	bool WithdrawMoney(Money amount);
	void DepositMoney(Money amount);
	AccountId GetAccountId();

private:
	Bank& m_bank;
	AccountId m_accountId;
};