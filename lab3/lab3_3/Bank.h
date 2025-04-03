#pragma once
#include <stdexcept>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

class Bank
{
public:
	explicit Bank(Money cash);

	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	 void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] Money GetCash() const;
	 Money GetAccountBalance(AccountId accountId) const;
	[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);
	 void DepositMoney(AccountId account, Money amount);
	[[nodiscard]] AccountId OpenAccount();
	[[nodiscard]] Money CloseAccount(AccountId accountId);
	bool IsAccountExisting(AccountId accountId) const; 
	Money GetDeposits();

private:
	Money m_totalCash;
	Money m_totalDeposits = 0;
	AccountId m_accountIdCounter = 0;
	std::unordered_map<AccountId, Money> m_accounts;
	void CheckAccountValid(AccountId accountId) const;
};