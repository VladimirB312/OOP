#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Task4/PrimeNumberGenerator.h"

//SCENARIO("Check prime number to 2")
//{
//	std::set<int> primeNumbers = GeneratePrimeNumbersSet(2);
//	REQUIRE(primeNumbers.empty());
//}
//
//SCENARIO("Check prime number 3")
//{
//	std::set<int> primeNumbers = GeneratePrimeNumbersSet(3);
//	std::set<int> numbers = { 2 };
//	REQUIRE(primeNumbers == numbers);
//}
//
//SCENARIO("Check prime number to 10")
//{
//	std::set<int> primeNumbers = GeneratePrimeNumbersSet(10);
//	std::set<int> numbers = { 2, 3, 5, 7 };
//	REQUIRE(primeNumbers == numbers);
//}
//
//SCENARIO("Check prime number to 100")
//{
//	std::set<int> primeNumbers = GeneratePrimeNumbersSet(100);
//	REQUIRE(primeNumbers.size() == 25);
//}

SCENARIO("Check prime number to 100000000")
{
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
	REQUIRE(primeNumbers.size() == 5761455);
}