#pragma once
#include "Actor.h"

class ActorWithCard : public Actor
{
public:
	ActorWithCard(Bank& bank, Money cash);
	bool TrySendMoney(ActorWithCard& actor, Money amount);
	bool TryWithdrawMoney(Money amount);
	void DepositMoney(Money amount);
	AccountId GetAccountId();
	bool IsAccountExisting();
	void OpenAccount();
	void CloseAccount();
	Money GetAccountBalance();
	virtual ~ActorWithCard() = default;

private:
	Bank& m_bank;
	AccountId m_accountId;
};