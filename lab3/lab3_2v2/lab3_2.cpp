#include "CalculatorUI.h"
#include <iostream>

int main()
{
	try
	{
		CalculatorUI calculatorUI(std::cin, std::cout);
		calculatorUI.Start();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}
