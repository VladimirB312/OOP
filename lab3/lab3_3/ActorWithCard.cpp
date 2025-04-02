#include "ActorWithCard.h"

ActorWithCard::ActorWithCard(Bank& bank, Money cash)
	: m_bank(bank)
	, Actor(cash)
	, m_accountId(bank.OpenAccount())
{
}

void ActorWithCard::SendMoney(std::unique_ptr<ActorWithCard>& actor, Money amount)
{
	m_bank.SendMoney(m_accountId, actor->GetAccountId(), amount);
}

bool ActorWithCard::WithdrawMoney(Money amount)
{
	if (m_bank.TryWithdrawMoney(m_accountId, amount))
	{
		m_cash += amount;
		return true;
	}

	return false;
}

void ActorWithCard::DepositMoney(Money amount)
{
	if (m_cash < amount)
	{
		return;
	}

	m_bank.DepositMoney(m_accountId, amount);
	m_cash -= amount;
}

AccountId ActorWithCard::GetAccountId()
{
	return m_accountId;
}
