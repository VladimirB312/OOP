#pragma once
#include "Actors.h"
#include "Bank.h"
#include <iostream>
#include <numeric>
#include <stdexcept>

void Economy(int iterationCount)
{
	Bank bank(3700);
	Homer homer(bank, 300);
	homer.DepositMoney(300);
	Marge marge(bank, 300);
	marge.DepositMoney(300);
	Apu apu(bank, 300);
	apu.DepositMoney(300);
	Burns burns(bank, 1300);
	burns.DepositMoney(1300);
	Chester chester(bank, 300);
	chester.DepositMoney(300);
	Smithers smithers(bank, 300);
	smithers.DepositMoney(300);
	Bart bart(300);
	Lisa lisa(300);
	Nelson nelson(300);

	for (; iterationCount >= 0; iterationCount--)
	{
		try
		{
			homer.Action(marge, burns, bart, lisa);
			marge.Action(apu);
			bart.Action(apu);
			lisa.Action(apu);
			apu.Action(burns);
			burns.Action(homer, smithers);
			nelson.Action(nelson, bart, apu);
			chester.Action(chester, homer, apu);
			smithers.Action(apu);
		}
		catch (const BankOperationError& ex)
		{
			std::cout << "error\n";
		}
	}

	Money allCash = bart.GetCash() + lisa.GetCash() + apu.GetCash() + nelson.GetCash() + smithers.GetCash();

	Money allDeposits = 0;
	allDeposits += bank.GetAccountBalance(homer.GetAccountId());
	allDeposits += bank.GetAccountBalance(marge.GetAccountId());
	allDeposits += bank.GetAccountBalance(apu.GetAccountId());
	allDeposits += bank.GetAccountBalance(burns.GetAccountId());
	allDeposits += bank.GetAccountBalance(chester.GetAccountId());
	if (bank.IsAccountExisting(smithers.GetAccountId()))
	{
		allDeposits += bank.GetAccountBalance(smithers.GetAccountId());
	}

	std::cout << "The amount of money in pockets: " << allCash << "\n";
	std::cout << "The amount of money in accounts: " << allDeposits << "\n";

	if (allCash != bank.GetCash())
	{
		std::cout << "The amount of cash the characters have is incorrect! \n";
		return;
	}

	if (allDeposits + allCash != 3700)
	{
		std::cout << "The total amount of all cash and non-cash money in accounts is not equal to the amounts in the bank!\n";
		return;
	}

	std::cout << "The amount of cash the characters have is the same as the amount of cash registered in the bank.\n";
	std::cout << "The total amount of all cash and non-cash funds in the accounts is equal to the amount that was originally deposited in the bank in cash.\n";
}