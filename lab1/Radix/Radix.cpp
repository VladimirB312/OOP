// Radix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <optional>
#include <cmath>
#include <list>

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

bool IsNumber(const char* str)
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

	throw std::invalid_argument("Invalid argument, value is not number!");
}

char IntToChar(int n)
{
	if (n >= 10)
	{
		return 'A' + n - 10;
	}

	return '0' + n;
}

bool IsCorrectValue(int sourceNotation, const std::string& value)
{
	std::string num = value;

	if (num[0] == '-')
	{
		num = num.substr(1);
	}

	if (num.size() == 0)
	{
		return false;
	}

	for (const auto& ch : num)
	{
		if (!isdigit(ch) && !isupper(ch))
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

bool IsValidInterval(int num)
{
	return num < 2 || num > 36;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: radix.exe <source notation> <destination notation> <value>\n");
	}

	if (!IsNumber(argv[1]) || !IsNumber(argv[2]))
	{
		throw std::invalid_argument("Invalid notation argument\nSource notation and destination notation must be number\n");
	}

	Args args;
	args.sourceNotation = std::stoi(argv[1]);
	args.destinationNotation = std::stoi(argv[2]);
	args.value = argv[3];

	if (IsValidInterval(args.sourceNotation) || IsValidInterval(args.destinationNotation))
	{
		throw std::invalid_argument("Invalid notation argument\nSource notation and destination notation must be from 2 to 36\n");
	}

	if (!IsCorrectValue(args.sourceNotation, args.value))
	{
		throw std::invalid_argument("Invalid value argument\nThe value must match the source notation\n");
	}

	return args;
}

int StringToInt(const std::string& str, int radix)
{
	int result = 0;
	std::string num = str;
	int isPositiveNum = (num[0] != '-');

	for (size_t i = isPositiveNum ? 0 : 1; i < num.size(); i++)
	{
		if ((INT_MAX - CharToInt(num[i])) / radix < result)
		{
			throw std::runtime_error("Overflow error!\n");
		}

		result *= radix;
		result += CharToInt(num[i]);
	}

	return isPositiveNum ? result : -result;
}

std::string IntToString(int n, int radix)
{
	std::string result;
	int isNegativeNum = false;
	if (n < 0)
	{
		isNegativeNum = true;
		n *= -1;
	}

	do
	{
		result.push_back(IntToChar(n % radix));
		n = n / radix;

	} while (n != 0);

	if (isNegativeNum)
	{
		result.push_back('-');
	}

	reverse(result.begin(), result.end());
	return result;
}

int main(int argc, char* argv[])
{
	try {
		const std::optional<Args> args = ParseArgs(argc, argv);

		int num = StringToInt(args->value, args->sourceNotation);

		std::cout << IntToString(num, args->destinationNotation) << "\n";
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}