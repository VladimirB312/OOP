#include <iostream>
#include <sstream>
#include <string>
#include "EvaluateExpression.h"

int main()
{
    try
    {
        std::string line;
        while (getline(std::cin, line))
        {
            std::istringstream expr(line);
            std::cout << Calculate(expr) << "\n";
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "ERROR";
    }

    return 0;
}