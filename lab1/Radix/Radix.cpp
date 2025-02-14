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

	throw std::runtime_error("Char is not a digit!");
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

	if (IsValidInterval(args.sourceNotation) || IsValidInterval(args.destinationNotation))
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

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;
	int sign = 1;
	std::string num = str;

	if (num[0] == '-')
	{
		sign = -1;
		num = num.substr(1);
	}

	for (size_t i = 0, j = num.size() - 1; i < num.size(); i++, j--)
	{
		if (result > (INT_MAX - CharToInt(num[j]) * pow(radix, i)))
		{
			wasError = true;
			std::cout << "Overflow error!\n";
			return 0;
		}
		result += CharToInt(num[j]) * pow(radix, i);
	}

	return result * sign;
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
	const std::optional<Args> args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool wasError = false;

	int num = StringToInt(args->value, args->sourceNotation, wasError);
	if (wasError)
	{
		return 1;
	}

	std::cout << IntToString(num, args->destinationNotation) << "\n";

	return 0;
}