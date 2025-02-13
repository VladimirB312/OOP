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

int CharToInt(const char ch)
{
	if (isdigit(ch))
	{
		return ch - '0';
	}

	if (isupper(ch))
	{
		return ch - 'A' + 10;
	}

	return INT_MAX;
}

char IntToChar(const int n)
{
	if (n >= 10)
	{
		return 'A' + n - 10;
	}

	return '0' + n;
}

bool IsCorrectValue(const int sourceNotation, const std::string& value)
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

int StringToInt(const std::string& str, const int radix, bool& wasError)
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

std::string IntToString(int n, const int radix)
{
	std::list<int> number;
	std::string result;

	if (n < 0)
	{
		result.push_back('-');
		n *= -1;
	}

	do
	{
		number.push_front(n % radix);
		n = n / radix;

	} while (n != 0);

	for (const auto& digit : number)
	{
		result.push_back(IntToChar(digit));
	}

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