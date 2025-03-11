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