#include <iostream>
#include "ProcessNumbers.h"

int main()
{
    try {
        std::vector<double> numbers = ReadNumbers(std::cin);
        numbers = ProcessNumbers(numbers);
        PrintSortedNumbers(std::cout, numbers);
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what();
    }

    return 0;
}
