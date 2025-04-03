#include "Economy.h"
#include <iostream>
#include <string>

int ParseArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		int result;
		std::cin >> result;
		return result;
	}

	if (argc == 2)
	{
		return std::stoi(argv[1]);
	}

	throw std::invalid_argument("invalid argument");
}

int main(int argc, char* argv[])
{
	try
	{		
		Economy(ParseArgs(argc, argv));
	}
	catch (const std::exception& ex)
	{
		std::cout << "ERROR!" << '\n';
		return 1;
	}

	return 0;
}
