#include "Actors.h"
#include <iostream>
#include <random>

namespace money
{
const Money HOMER_TO_MARGE = 100;
const Money HOMER_TO_BURNS = 100;
const Money HOMER_TO_BART = 30;
const Money HOMER_TO_LISA = 30;
const Money MARGE_TO_APU = 100;
const Money BART_TO_APU = 10;
const Money LISA_TO_APU = 10;
const Money APU_TO_BURNS = 100;
const Money BURNS_TO_HOMER = 400;
const Money BURNS_TO_SMITHERS = 400;
const Money NELSON_TO_APU = 10;
const Money CHESTER_TO_APU = 50;
const Money SMITHERS_TO_APU = 150;
} // namespace money

namespace
{
int GetRandomNum(int start, int end)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(start, end);
	return dist(gen);
}
} // namespace

// HOMER
Homer::Homer(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Homer::Action(ActorWithCard& marge,
	ActorWithCard& burns,
	Actor& bart,
	Actor& lisa)
{
	if (TrySendMoney(marge, money::HOMER_TO_MARGE))
	{
		std::cout << "Homer sent " << money::HOMER_TO_MARGE << " money to Marge. \n";
	}

	if (TrySendMoney(burns, money::HOMER_TO_BURNS))
	{
		std::cout << "Homer paid " << money::HOMER_TO_BURNS << " money for the electricity. \n";
	}

	if (TryWithdrawMoney(money::HOMER_TO_BART) && GiveMoney(bart, money::HOMER_TO_BART))
	{

		std::cout << "Homer gave " << money::HOMER_TO_BART << " money to Bart. \n";
	}

	if (TryWithdrawMoney(money::HOMER_TO_LISA) && GiveMoney(lisa, money::HOMER_TO_LISA))
	{
		std::cout << "Homer gave " << money::HOMER_TO_LISA << " money to Lisa. \n";
	}
}

// MARGE
Marge::Marge(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Marge::Action(ActorWithCard& apu)
{
	if (TrySendMoney(apu, money::MARGE_TO_APU))
	{
		std::cout << "Marge bought groceries from Apu for " << money::MARGE_TO_APU << " money. \n";
	}
}

// BART
Bart::Bart(Money cash)
	: Actor(cash)
{
}

void Bart::Action(Actor& apu)
{
	if (GiveMoney(apu, money::BART_TO_APU))
	{
		std::cout << "Bart bought goods from Apu for " << money::BART_TO_APU << " money. \n";
	}
}

// LISA
Lisa::Lisa(Money cash)
	: Actor(cash)
{
}

void Lisa::Action(Actor& apu)
{
	if (GiveMoney(apu, money::LISA_TO_APU))
	{
		std::cout << "Lisa bought goods from Apu for " << money::LISA_TO_APU << " money. \n";
	}
}

// APU
Apu::Apu(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Apu::Action(ActorWithCard& burns)
{
	DepositMoney(GetCash());

	if (TrySendMoney(burns, money::APU_TO_BURNS))
	{
		std::cout << "Apu paid " << money::APU_TO_BURNS << " money for the electricity. \n";
	}
}

// BURNS
Burns::Burns(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Burns::Action(ActorWithCard& homer, ActorWithCard& smithers)
{
	if (TrySendMoney(homer, money::BURNS_TO_HOMER))
	{
		std::cout << "Burns paid Homer " << money::BURNS_TO_HOMER << " salary. \n";
	}

	if (TrySendMoney(smithers, money::BURNS_TO_SMITHERS))
	{
		std::cout << "Burns paid Smithers " << money::BURNS_TO_SMITHERS << " salary. \n";
	}
}

// NELSON
Nelson::Nelson(Money cash)
	: Actor(cash)
{
}

void Nelson::Action(Actor& self, Actor& bart, ActorWithCard& apu)
{
	if (GiveMoney(apu, money::NELSON_TO_APU))
	{
		std::cout << "Nelson bought goods from Apu for " << money::CHESTER_TO_APU << " money. \n";
	}

	if (GetRandomNum(1, 6) != 2)
	{
		return;
	}

	int moneyToSteal = GetRandomNum(10, 50);
	if (bart.GiveMoney(self, moneyToSteal))
	{
		std::cout << "Nelson stole " << moneyToSteal << " from Bart. \n";
	}
}

// CHESTER
Chester::Chester(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Chester::Action(ActorWithCard& self, ActorWithCard& homer, ActorWithCard& apu)
{
	if (TrySendMoney(apu, money::CHESTER_TO_APU))
	{
		std::cout << "Chester bought goods from Apu for " << money::CHESTER_TO_APU << " money. \n";
	}

	if (GetRandomNum(1, 6) != 4)
	{
		return;
	}

	int moneyToSteal = GetRandomNum(30, 200);
	if (TrySendMoney(self, moneyToSteal))
	{
		std::cout << "Chester stole " << moneyToSteal << " from Homer's account. \n";
	}
}

// SMITHERS
Smithers::Smithers(Bank& bank, Money cash)
	: ActorWithCard(bank, cash)
{
}

void Smithers::Action(ActorWithCard& apu)
{
	if (!IsAccountExisting())
	{
		OpenAccount();
		DepositMoney(m_cash);
		std::cout << "Smithers has opened a new account.\n";
	}

	if (TrySendMoney(apu, money::SMITHERS_TO_APU))
	{
		std::cout << "Smithers bought goods from Apu for " << money::SMITHERS_TO_APU << " money. \n";
	}

	if (GetRandomNum(1, 6) == 3)
	{
		CloseAccount();
		std::cout << "Smithers closed the account.\n";
	}
}
