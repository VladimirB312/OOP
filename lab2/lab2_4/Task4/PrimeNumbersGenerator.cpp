#include "PrimeNumberGenerator.h"
#include <vector>
#include <iostream>

const int MIN_NUMBER_COUNT = 2;
const int MAX_NUMBER_COUNT = 100000000;

std::vector<bool> GeneratePrimeNumberBoolVector(int upperBound)
{	
	std::vector<bool> numbers(upperBound, true);
	for (int p = MIN_NUMBER_COUNT; p * p < upperBound; p += p == 2 ? 1 : 2)
	{
		if (!numbers[p])
		{
			continue;
		}
		for (int i = p * p; i < upperBound; i += p)
		{
			numbers[i] = false;
		}
	}

	return numbers;
}

std::set<int> ConvertBoolVectorToSet(const std::vector<bool>& numbers)
{
	std::set<int> primeNumbers;
	for (int i = MIN_NUMBER_COUNT; i < numbers.size(); i++)
	{
		if (numbers[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}

void CheckUpperBound(int upperBound)
{
	if (upperBound <= MIN_NUMBER_COUNT || upperBound > MAX_NUMBER_COUNT)
	{
		throw std::invalid_argument("Upper bound must be from 3 to 100000000!");
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	CheckUpperBound(upperBound);
	std::vector<bool> numbers = GeneratePrimeNumberBoolVector(upperBound);
	return ConvertBoolVectorToSet(numbers);
}

void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers)
{
	bool isFirst = true;
	for (auto num : primeNumbers)
	{
		if (!isFirst)
		{
			output << " ";
		}
		output << num;
		isFirst = false;
	}
}