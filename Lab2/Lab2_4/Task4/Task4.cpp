#include <iostream>
#include <set>
#include <vector>
#include <string>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    std::vector<bool> numbers(upperBound, true);
    numbers[0] = numbers[1] = false;

    int p = 2;
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

    for (int i = 0; i < upperBound; i++)
    {
        if (numbers[i])
        {
            primeNumbers.insert(i);
        }
    }

    return primeNumbers;
}

int ParseNumberCount(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid argument");
    }

    int numbersCount = std::stoi(argv[1]);
    if (numbersCount < 2 || numbersCount > 100000000)
    {
        throw std::invalid_argument("Input number from 2 to 100000000!");
    }

    return numbersCount;
}

void PrintPrimeNumbers(const std::set<int>& primeNumbers)
{
    for (auto num : primeNumbers)
    {
        std::cout << num << " ";
    }
}

int main(int argc, char* argv[]) 
{
    try {
        int numbersCount = ParseNumberCount(argc, argv);
        std::set<int> primeNumbers = GeneratePrimeNumbersSet(numbersCount);
        PrintPrimeNumbers(primeNumbers);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }

    return 0;
}