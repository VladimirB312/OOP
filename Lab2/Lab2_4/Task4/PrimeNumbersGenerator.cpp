#include "PrimeNumberGenerator.h"
#include <vector>
#include <iostream>

std::vector<bool> GeneratePrimeNumberBoolVector(int upperBound)
{
    std::vector<bool> numbers(upperBound, true);

    int p = MIN_NUMBER_COUNT;
    while (p * p < upperBound)
    {
        if (numbers[p])
        {
            for (int i = p * p; i < upperBound; i += p)
            {
                numbers[i] = false;
            }
        }
        p++;
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

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{    
    std::vector<bool> numbers = GeneratePrimeNumberBoolVector(upperBound);
    return ConvertBoolVectorToSet(numbers);    
}

void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers)
{
    for (auto num : primeNumbers)
    {
        output  << num << " ";
    }
}