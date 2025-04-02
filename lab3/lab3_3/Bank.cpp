#include "Bank.h"

namespace
{
void CheckAmountValid(Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("The amount must not be negative");
	}
}
} // namespace

Bank::Bank(Money cash)
	: m_totalCash(cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Cash cannot be negative");
	}
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	CheckAccountValid(srcAccountId);
	CheckAccountValid(dstAccountId);
	CheckAmountValid(amount);

	if (m_accounts[srcAccountId] < amount)
	{
		throw BankOperationError("Not enough money in the account");
	}

	m_accounts[srcAccountId] -= amount;
	m_accounts[dstAccountId] += amount;
}

Money Bank::GetCash() const
{
	return m_totalCash;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
	CheckAccountValid(accountId);

	return m_accounts.at(accountId);
}

// void Bank::WithdrawMoney(AccountId account, Money amount)
//{
//	CheckExistenceAccount(account);
//
//	if (m_accounts[account] < amount)
//	{
//		throw BankOperationError("Not enough money in the account");
//	}
//
//	if (amount < 0)
//	{
//		throw std::out_of_range("The money to withdraw cannot be negative");
//	}
//
//	m_totalCash += amount;
//	m_accounts[account] -= amount;
// }

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
	CheckAccountValid(account);
	CheckAmountValid(amount);

	if (m_accounts[account] < amount)
	{
		return false;
	}

	m_totalCash += amount;
	m_accounts[account] -= amount;

	return true;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
	CheckAccountValid(account);

	if (amount > m_totalCash)
	{
		throw BankOperationError("The amount is greater than the available amount of money");
	}

	CheckAmountValid(amount);

	m_totalCash -= amount;
	m_accounts[account] += amount;
}

AccountId Bank::OpenAccount()
{
	m_accountIdCounter++;
	m_accounts[m_accountIdCounter] = 0;

	return m_accountIdCounter;
}

Money Bank::CloseAccount(AccountId accountId)
{
	CheckAccountValid(accountId);

	Money refund = m_accounts[accountId];
	m_accounts.erase(accountId);
	m_totalCash += refund;

	return refund;
}

void Bank::CheckAccountValid(AccountId accountId) const
{
	if (auto it = m_accounts.find(accountId); it == m_accounts.end())
	{
		throw BankOperationError("The account doesn't exist");
	}
}