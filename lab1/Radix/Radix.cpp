// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <optional>

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

bool IsNumber(char* str)
{
	std::string num(str);
	for (const auto& ch : num)
	{
		if (!std::isdigit(ch))
		{
			return false;
		}
	}

	return true;
}

int CharToInt(char ch)
{
	if (isdigit(ch))
	{
		return ch - '0';
	}

	if (isupper(ch))
	{
		return ch - 'A' + 10;
	}
}

bool IsCorrectValue(int sourceNotation, std::string value)
{
	for (const auto& ch : value)
	{
		if (!isdigit(ch) || !isupper(ch))
		{
			return false;
		}

		if (sourceNotation <= CharToInt(ch))
		{
			return false;
		}
	}

	return true;
}

std::optional<Args> ParseArgs(const int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}

	if (!IsNumber(argv[1]) || !IsNumber(argv[2]))
	{
		std::cout << "Invalid notation argument\n"
			<< "Source notation and destination notation must be number\n";
		return std::nullopt;
	}

	Args args;
	args.sourceNotation = std::stoi(argv[1]);
	args.destinationNotation = std::stoi(argv[2]);
	args.value = argv[3];

	if (args.sourceNotation < 2 || args.sourceNotation > 36 || args.destinationNotation < 2 || args.destinationNotation > 36)
	{
		std::cout << "Invalid notation argument\n"
			<< "Source notation and destination notation must be from 2 to 36\n";
		return std::nullopt;
	}

	if (!IsCorrectValue(args.sourceNotation, args.value))
	{
		std::cout << "Invalid value argument\n"
			<< "The value must match the source notation\n";
		return std::nullopt;
	}

	return args;
}

int main(int argc, char* argv[])
{
	const std::optional<Args> args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool wasError = false;

	return 0;
}