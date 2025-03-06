#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Task4/PrimeNumberGenerator.h"

SCENARIO("Generate prime numbers")
{
	WHEN("upper bound is 2")
	{		
		THEN("should throw an exception")
		{
			CHECK_THROWS_AS(GeneratePrimeNumbersSet(2), std::invalid_argument);
		}
	}

	WHEN("upper bound is 3")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(3);
		THEN("set of prime numbers must contain only digit 2")
		{
			CHECK(primeNumbers == std::set<int>{2});
		}
	}

	WHEN("upper bound is 100")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(100);
		THEN("set of prime numbers must contains 25 numbers")
		{
			CHECK(primeNumbers.size() == 25);
		}
	}

	WHEN("upper bound is 100000001")
	{
		THEN("should throw an exception")
		{
			CHECK_THROWS_AS(GeneratePrimeNumbersSet(100000001), std::invalid_argument);
		}
	}

	WHEN("upper bound is 100000000")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
		THEN("set of prime numbers must contains 5761455 prime numbers")
		{
			CHECK(primeNumbers.size() == 5761455);
		}
	}

	WHEN("upper bound is 99999999")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
		THEN("set of prime numbers must contains 5761455 prime numbers")
		{
			CHECK(primeNumbers.size() == 5761455);
		}
	}
}

SCENARIO("Print prime numbers")
{
	std::ostringstream output;
	WHEN("upper bound is 3")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(3);
		PrintPrimeNumbers(output, primeNumbers);
		THEN("output must contain prime numbers from 2 to 3")
		{
			CHECK(output.str() == "2");
		}
	}

	WHEN("upper bound is 10")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(10);
		PrintPrimeNumbers(output, primeNumbers);
		THEN("output must contain prime numbers from 2 to 10")
		{
			CHECK(output.str() == "2 3 5 7");
		}
	}

	WHEN("upper bound is 20")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(20);
		PrintPrimeNumbers(output, primeNumbers);
		THEN("output must contain prime numbers from 2 to 20")
		{
			CHECK(output.str() == "2 3 5 7 11 13 17 19");
		}
	}

	WHEN("upper bound is 100")
	{
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(100);
		PrintPrimeNumbers(output, primeNumbers);
		THEN("output must contain prime numbers from 2 to 100")
		{
			CHECK(output.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97");
		}
	}
}