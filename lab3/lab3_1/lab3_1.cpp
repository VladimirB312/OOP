#include <iostream>
#include "CarController.h"

int main()
{
	try
	{
		Car car;
		CarController carController(std::cin, std::cout, car);
		carController.StartDriving();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
