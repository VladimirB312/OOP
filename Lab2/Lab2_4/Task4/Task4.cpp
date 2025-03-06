#include <iostream>
#include <set>
#include <vector>
#include <string>

#include "PrimeNumberGenerator.h"

int ParseNumberCount(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid argument");
    }

    int numbersCount = std::stoi(argv[1]);
    if (numbersCount <= MIN_NUMBER_COUNT || numbersCount > MAX_NUMBER_COUNT)
    {
        throw std::invalid_argument("Upper bound must be from 3 to 100000000!");
    }

    return numbersCount;
}

int main(int argc, char* argv[]) 
{
    try {
        int numbersCount = ParseNumberCount(argc, argv);
        std::set<int> primeNumbers = GeneratePrimeNumbersSet(numbersCount);
        PrintPrimeNumbers(std::cout, primeNumbers);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }

    return 0;
}