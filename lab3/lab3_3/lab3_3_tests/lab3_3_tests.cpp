#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Actor.h"
#include "../ActorWithCard.h"
#include "../Bank.h"

SCENARIO("create bank")
{
	WHEN("creating a bank with 100 units of money")
	{
		Bank bank(100);
		THEN("money in cash should be 100")
		{
			CHECK(bank.GetCash() == 100);
		}
	}

	WHEN("creating a bank with 1 units of money")
	{
		Bank bank(1);
		THEN("money in cash should be 1")
		{
			CHECK(bank.GetCash() == 1);
		}
	}

	WHEN("creating a bank with 0 units of money")
	{
		Bank bank(0);
		THEN("money in cash should be 100")
		{
			CHECK(bank.GetCash() == 0);
		}
	}

	WHEN("creating a bank with negative units of money")
	{
		THEN("an exception must be thrown")
		{
			CHECK_THROWS_AS(Bank(-1), BankOperationError);
		}
	}

	WHEN("creating a bank with negative units of money")
	{
		THEN("an exception must be thrown")
		{
			CHECK_THROWS_AS(Bank(-100), BankOperationError);
		}
	}
}

SCENARIO("open account and get balance")
{
	GIVEN("bank with 0 units of money")
	{
		Bank bank(0);
		WHEN("open first account")
		{
			AccountId id = bank.OpenAccount();
			THEN("account id must be 1 and account balance must be 0")
			{
				CHECK(id == 1);
				CHECK(bank.GetAccountBalance(id) == 0);
			}
			AND_WHEN("open some more accounts")
			{
				AccountId id2 = bank.OpenAccount();
				AccountId id3 = bank.OpenAccount();
				AccountId id4 = bank.OpenAccount();
				AccountId id5 = bank.OpenAccount();
				THEN("their id's must be unique and accounts balance must be 0")
				{
					CHECK(id2 == 2);
					CHECK(id3 == 3);
					CHECK(id4 == 4);
					CHECK(id5 == 5);
					CHECK(bank.GetAccountBalance(id2) == 0);
					CHECK(bank.GetAccountBalance(id3) == 0);
					CHECK(bank.GetAccountBalance(id4) == 0);
					CHECK(bank.GetAccountBalance(id5) == 0);
				}
			}
		}

		WHEN("trying to request a balance from a non-existent account")
		{
			THEN("an exception must be thrown")
			{
				CHECK_THROWS_AS(bank.GetAccountBalance(1), BankOperationError);
			}
		}
	}
}

SCENARIO("deposit money")
{
	GIVEN("bank with 100 units of money and one account")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		WHEN("deposit 10 units of cash in the bank")
		{
			bank.DepositMoney(id, 10);
			THEN("total cash decreases by the amount and money in the account increases")
			{
				CHECK(bank.GetCash() == 90);
				CHECK(bank.GetAccountBalance(id) == 10);
			}
		}

		WHEN("deposit 100 units of cash in the bank")
		{
			bank.DepositMoney(id, 100);
			THEN("total cash decreases by the amount and money in the account increases")
			{
				CHECK(bank.GetCash() == 0);
				CHECK(bank.GetAccountBalance(id) == 100);
			}
		}

		WHEN("deposit 1 units of cash in the bank")
		{
			bank.DepositMoney(id, 1);
			THEN("total cash decreases by the amount and money in the account increases")
			{
				CHECK(bank.GetCash() == 99);
				CHECK(bank.GetAccountBalance(id) == 1);
			}
		}

		WHEN("deposit 0 units of cash in the bank")
		{
			bank.DepositMoney(id, 0);
			THEN("total cash decreases by the amount and money in the account increases")
			{
				CHECK(bank.GetCash() == 100);
				CHECK(bank.GetAccountBalance(id) == 0);
			}
		}

		WHEN("trying to deposit -1 units of cash in the bank")
		{
			THEN("an exception must be thrown")
			{
				CHECK_THROWS_AS(bank.DepositMoney(id, -1), std::out_of_range);
			}
		}

		WHEN("trying to deposit more than there is money in cash")
		{
			THEN("an exception must be thrown")
			{
				CHECK_THROWS_AS(bank.DepositMoney(id, 101), BankOperationError);
			}
		}

		WHEN("trying to deposit  money into a non-existent account")
		{
			THEN("an exception must be thrown")
			{
				CHECK_THROWS_AS(bank.DepositMoney(15, 50), BankOperationError);
			}
		}
	}
}

SCENARIO("close account")
{
	GIVEN("bank with 50 units of cash money and 50 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 50);
		WHEN("the account closes")
		{
			THEN("returned money should be equal to the money on the account and the total cash of the bank should increase by this amount")
			{
				CHECK(bank.CloseAccount(id) == 50);
				CHECK(bank.GetCash() == 100);

				AND_WHEN("trying to get account balance")
				{
					THEN("an exception must be thrown")
					{
						CHECK_THROWS_AS(bank.GetAccountBalance(id), BankOperationError);
					}

					AND_WHEN("trying to close an already closed account")
					{
						THEN("an exception must be thrown")
						{
							CHECK_THROWS_AS(bank.CloseAccount(id), BankOperationError);
						}
					}
				}
			}
		}

		WHEN("trying to close a non-existing account")
		{
			THEN("an exception must be thrown")
			{
				CHECK_THROWS_AS(bank.CloseAccount(25), BankOperationError);
			}
		}
	}

	GIVEN("bank with 100 units of cash money and 0 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		WHEN("the account closes")
		{
			THEN("returned money should be equal to the money on the account and the total cash of the bank should increase by this amount")
			{
				CHECK(bank.CloseAccount(id) == 0);
				CHECK(bank.GetCash() == 100);
			}
		}
	}

	GIVEN("bank with 0 units of cash money and 100 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 100);
		WHEN("the account closes")
		{
			THEN("returned money should be equal to the money on the account and the total cash of the bank should increase by this amount")
			{
				CHECK(bank.CloseAccount(id) == 100);
				CHECK(bank.GetCash() == 100);
			}
		}
	}

	GIVEN("bank with 1 units of cash money and 99 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 99);
		WHEN("the account closes")
		{
			THEN("returned money should be equal to the money on the account and the total cash of the bank should increase by this amount")
			{
				CHECK(bank.CloseAccount(id) == 99);
				CHECK(bank.GetCash() == 100);
			}
		}
	}

	GIVEN("bank with 99 units of cash money and 1 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 1);
		WHEN("the account closes")
		{
			THEN("returned money should be equal to the money on the account and the total cash of the bank should increase by this amount")
			{
				CHECK(bank.CloseAccount(id) == 1);
				CHECK(bank.GetCash() == 100);
			}
		}
	}
}

SCENARIO("withdraw money")
{
	GIVEN("bank with 50 units of cash money and 50 units on deposit")
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 50);
		WHEN("trying to widhdraw 25 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return true and total cash will increase by 25"
				 "and the amount on the account will decrease by that amount")
			{
				CHECK(bank.TryWithdrawMoney(id, 25));
				CHECK(bank.GetCash() == 75);
				CHECK(bank.GetAccountBalance(id) == 25);
			}
		}

		WHEN("trying to widhdraw 50 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return true and total cash will increase by 25"
				 "and the amount on the account will decrease by that amount")
			{
				CHECK(bank.TryWithdrawMoney(id, 50));
				CHECK(bank.GetCash() == 100);
				CHECK(bank.GetAccountBalance(id) == 0);
			}
		}

		WHEN("trying to widhdraw 49 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return true and total cash will increase by 25"
				 "and the amount on the account will decrease by that amount")
			{
				CHECK(bank.TryWithdrawMoney(id, 49));
				CHECK(bank.GetCash() == 99);
				CHECK(bank.GetAccountBalance(id) == 1);
			}
		}

		WHEN("trying to widhdraw 0 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return true and total cash will increase by 25"
				 "and the amount on the account will decrease by that amount")
			{
				CHECK(bank.TryWithdrawMoney(id, 0));
				CHECK(bank.GetCash() == 50);
				CHECK(bank.GetAccountBalance(id) == 50);
			}
		}

		WHEN("trying to widhdraw 1 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return true and total cash will increase by 25"
				 "and the amount on the account will decrease by that amount")
			{
				CHECK(bank.TryWithdrawMoney(id, 1));
				CHECK(bank.GetCash() == 51);
				CHECK(bank.GetAccountBalance(id) == 49);
			}
		}

		WHEN("trying to widhdraw 51 units of deposit money")
		{
			THEN("TryWidthdrawMoney should return false and total cash will not change"
				 "and the amount on the account will not change")
			{
				CHECK(!bank.TryWithdrawMoney(id, 51));
				CHECK(bank.GetCash() == 50);
				CHECK(bank.GetAccountBalance(id) == 50);
			}
		}

		WHEN("trying to widhdraw -1 units of deposit money")
		{
			THEN("An exception must be thrown and total cash will not change"
				 "and the amount on the account will not change")
			{
				CHECK_THROWS_AS(bank.TryWithdrawMoney(id, -1), std::out_of_range);
				CHECK(bank.GetCash() == 50);
				CHECK(bank.GetAccountBalance(id) == 50);
			}
		}

		WHEN("trying to widhdraw money from a non-existent account")
		{
			THEN("An exception must be thrown and total cash will not change")
			{
				CHECK_THROWS_AS(bank.TryWithdrawMoney(16, 25), BankOperationError);
				CHECK(bank.GetCash() == 50);
			}
		}
	}
}

SCENARIO("send money")
{
	GIVEN("bank with no cash money and two accounts with 25 units of money")
	{
		Bank bank(50);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		bank.DepositMoney(id1, 25);
		bank.DepositMoney(id2, 25);
		WHEN("send all money from first account to second")
		{
			bank.SendMoney(id1, id2, 25);
			THEN("there should be 0 money in the first account and 50 in the second")
			{
				CHECK(bank.GetAccountBalance(id1) == 0);
				CHECK(bank.GetAccountBalance(id2) == 50);
			}

			AND_WHEN("send all the money from the second account to the first")
			{
				bank.SendMoney(id2, id1, 50);
				THEN("there should be 50 money in the first account and 0 in the second")
				{
					CHECK(bank.GetAccountBalance(id1) == 50);
					CHECK(bank.GetAccountBalance(id2) == 0);
				}
			}
		}

		WHEN("send 10 units of money from first account to second")
		{
			bank.SendMoney(id1, id2, 10);
			THEN("there should be 15 money in the first account and 35 in the second")
			{
				CHECK(bank.GetAccountBalance(id1) == 15);
				CHECK(bank.GetAccountBalance(id2) == 35);
			}
		}

		WHEN("send 24 units of money from first account to second")
		{
			bank.SendMoney(id1, id2, 24);
			THEN("there should be 15 money in the first account and 49 in the second")
			{
				CHECK(bank.GetAccountBalance(id1) == 1);
				CHECK(bank.GetAccountBalance(id2) == 49);
			}
		}

		WHEN("send 1 units of money from first account to second")
		{
			bank.SendMoney(id1, id2, 1);
			THEN("there should be 24 money in the first account and 26 in the second")
			{
				CHECK(bank.GetAccountBalance(id1) == 24);
				CHECK(bank.GetAccountBalance(id2) == 26);
			}
		}

		WHEN("send 0 units of money from first account to second")
		{
			bank.SendMoney(id1, id2, 0);
			THEN("there should be 25 money in the first account and 25 in the second")
			{
				CHECK(bank.GetAccountBalance(id1) == 25);
				CHECK(bank.GetAccountBalance(id2) == 25);
			}
		}

		WHEN("send -1 units of money from first account to second")
		{
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(bank.SendMoney(id1, id2, -1), std::out_of_range);
			}
		}

		WHEN("send 26 units of money from first account to second")
		{
			THEN("an exception should be thrown and account balance will not change")
			{
				CHECK_THROWS_AS(bank.SendMoney(id1, id2, 26), BankOperationError);
				CHECK(bank.GetAccountBalance(id1) == 25);
				CHECK(bank.GetAccountBalance(id2) == 25);
			}
		}

		WHEN("send money from first account to non-existent acount")
		{
			THEN("an exception should be thrown and frist account balance will not change")
			{
				CHECK_THROWS_AS(bank.SendMoney(id1, 7, 5), BankOperationError);
				CHECK(bank.GetAccountBalance(id1) == 25);
			}
		}

		WHEN("send money from non-existent acount account to second")
		{
			THEN("an exception should be thrown and second account balance will not change")
			{
				CHECK_THROWS_AS(bank.SendMoney(7, id2, 5), BankOperationError);
				CHECK(bank.GetAccountBalance(id2) == 25);
			}
		}

		WHEN("send money from non-existent acount to non-existent acount")
		{
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(bank.SendMoney(7, 9, 5), BankOperationError);
			}
		}
	}
}

SCENARIO("give and recieve money")
{
	GIVEN("two actors with 50 units of cash money")
	{
		auto actorOne = std::make_unique<Actor>(50);
		auto actorTwo = std::make_unique<Actor>(50);
		WHEN("give all money from actor one to actor two")
		{
			THEN("GiveMoney should be true and the amount of cash of the first actor should be 0 and the second actor 100")
			{
				CHECK(actorOne->GiveMoney(actorTwo, 50));
				CHECK(actorOne->GetCash() == 0);
				CHECK(actorTwo->GetCash() == 100);
			}
		}

		WHEN("give 25 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be true and the amount of cash of the first actor should be 25 and the second actor 75")
			{
				CHECK(actorOne->GiveMoney(actorTwo, 25));
				CHECK(actorOne->GetCash() == 25);
				CHECK(actorTwo->GetCash() == 75);
			}
		}

		WHEN("give 49 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be true and the amount of cash of the first actor should be 1 and the second actor 99")
			{
				CHECK(actorOne->GiveMoney(actorTwo, 49));
				CHECK(actorOne->GetCash() == 1);
				CHECK(actorTwo->GetCash() == 99);
			}
		}

		WHEN("give 1 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be true and the amount of cash of the first actor should be 49 and the second actor 51")
			{
				CHECK(actorOne->GiveMoney(actorTwo, 1));
				CHECK(actorOne->GetCash() == 49);
				CHECK(actorTwo->GetCash() == 51);
			}
		}

		WHEN("give 0 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be true and the amount of cash of the first and second actors will be unchanged")
			{
				CHECK(actorOne->GiveMoney(actorTwo, 0));
				CHECK(actorOne->GetCash() == 50);
				CHECK(actorTwo->GetCash() == 50);
			}
		}

		WHEN("give -1 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be false and the amount of cash of the first and second actors will be unchanged")
			{
				CHECK(!actorOne->GiveMoney(actorTwo, -1));
				CHECK(actorOne->GetCash() == 50);
				CHECK(actorTwo->GetCash() == 50);
			}
		}

		WHEN("give 51 units of money from actor one to actor two")
		{
			THEN("GiveMoney should be false and the amount of cash of the first and second actors will be unchanged")
			{
				CHECK(!actorOne->GiveMoney(actorTwo, 51));
				CHECK(actorOne->GetCash() == 50);
				CHECK(actorTwo->GetCash() == 50);
			}
		}
	}
}

SCENARIO("deposit and withdraw money")
{
	GIVEN("bank and actor with 50 units of cash money")
	{
		Bank bank(50);
		auto actor = std::make_unique<ActorWithCard>(bank, 50);
		WHEN("actor deposit 50 unit of money to account")
		{
			actor->DepositMoney(25);
			THEN("the cash in the bank must be 25, the actor must have 25, and his account must have 25.")
			{
				CHECK(bank.GetCash() == 25);
				CHECK(actor->GetCash() == 25);
				CHECK(bank.GetAccountBalance(actor->GetAccountId()) == 25);
			}

			AND_WHEN("actor withdraw 25 units of money")
			{
				THEN("WithdrawMoney should be true and cash in the bank must be 50, the actor must have 50, and his account must have 0")
				{
					CHECK(actor->WithdrawMoney(25));
					CHECK(bank.GetCash() == 50);
					CHECK(actor->GetCash() == 50);
					CHECK(bank.GetAccountBalance(actor->GetAccountId()) == 0);
				}
			}
		}
		WHEN("tryint to withdrawmoney")
		{
			THEN("WithdrawMoney should be false and cash will be unchanged")
			{
				CHECK(!actor->WithdrawMoney(25));
				CHECK(bank.GetCash() == 50);
				CHECK(actor->GetCash() == 50);
				CHECK(bank.GetAccountBalance(actor->GetAccountId()) == 0);
			}
		}
		WHEN("to deposit more than the actor has")
		{
			actor->DepositMoney(100);
			THEN("cash will be unchanged")
			{
				CHECK(bank.GetCash() == 50);
				CHECK(actor->GetCash() == 50);
				CHECK(bank.GetAccountBalance(actor->GetAccountId()) == 0);
			}
		}
	}
}

SCENARIO("send money from actor to actor")
{
	GIVEN("bank with 100 units of cash and two actor with 50 units of deposit money")
	{
		Bank bank(100);
		auto actorOne = std::make_unique<ActorWithCard>(bank, 50);
		auto actorTwo = std::make_unique<ActorWithCard>(bank, 50);
		actorOne->DepositMoney(50);
		actorTwo->DepositMoney(50);
		WHEN("actorOne send 50 units to actorTwo")
		{
			actorOne->SendMoney(actorTwo, 50);
			THEN("the first actor's account should be 0 and the second actor's should be 100")
			{
				CHECK(bank.GetAccountBalance(actorOne->GetAccountId()) == 0);
				CHECK(bank.GetAccountBalance(actorTwo->GetAccountId()) == 100);
			}

			AND_WHEN("first actor trying to send more money")
			{				
				THEN("an exception must be thrown and the balance of the accounts will not change")
				{
					CHECK_THROWS_AS(actorOne->SendMoney(actorTwo, 50), BankOperationError);
					CHECK(bank.GetAccountBalance(actorOne->GetAccountId()) == 0);
					CHECK(bank.GetAccountBalance(actorTwo->GetAccountId()) == 100);
				}
			}
		}
	}
}