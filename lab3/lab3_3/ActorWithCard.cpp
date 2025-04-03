#include "ActorWithCard.h"

ActorWithCard::ActorWithCard(Bank& bank, Money cash)
	: m_bank(bank)
	, Actor(cash)
	, m_accountId(bank.OpenAccount())
{
}

bool ActorWithCard::TrySendMoney(ActorWithCard& actor, Money amount)
{
	if (!m_bank.IsAccountExisting(actor.GetAccountId()))
	{
		return false;
	}

	if (m_bank.GetAccountBalance(m_accountId) < amount)
	{
		return false;
	}

	m_bank.SendMoney(m_accountId, actor.GetAccountId(), amount);

	return true;
}

bool ActorWithCard::TryWithdrawMoney(Money amount)
{
	if (m_bank.GetAccountBalance(m_accountId) < amount)
	{
		return false;
	}

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

bool ActorWithCard::IsAccountExisting()
{
	return m_bank.IsAccountExisting(m_accountId);
}

void ActorWithCard::OpenAccount()
{
	m_accountId = m_bank.OpenAccount();
}

void ActorWithCard::CloseAccount()
{
	m_cash += m_bank.CloseAccount(m_accountId);
}

Money ActorWithCard::GetAccountBalance()
{
	return m_bank.GetAccountBalance(m_accountId);
}
