#include "ProcessNumbers.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <numeric>

struct PositiveNumbersInfo
{
	size_t count = 0;
	double sum = 0;
};

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> result;

	double number;
	while (input >> number)
	{
		result.push_back(number);
	}

	if (input.fail() && !input.eof())
	{
		throw std::runtime_error("ERROR");
	}

	return result;
}

void PrintSortedNumbers(std::ostream& output, std::vector<double> numbers)
{
	std::sort(numbers.begin(), numbers.end());
	for (size_t i = 0; i < numbers.size(); i++)
	{
		output << std::fixed << std::setprecision(3) << numbers[i];
		if (i != numbers.size() - 1)
		{
			output << " ";
		}
	}
}

PositiveNumbersInfo GetAverageOfPositiveNumbers(const std::vector<double>& numbers)
{
	return std::accumulate(numbers.begin(), numbers.end(), PositiveNumbersInfo(),
		[](PositiveNumbersInfo acc, double current)
		{
			if (current > 0)
			{
				acc.sum += current;
				acc.count++;
			}
			return acc;
		});
}

std::vector<double> ProcessNumbers(std::vector<double>& numbers)
{
	PositiveNumbersInfo positiveNumbers = GetAverageOfPositiveNumbers(numbers);

	if (positiveNumbers.count == 0)
	{
		return numbers;
	}

	double average = positiveNumbers.sum / positiveNumbers.count;

	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		[average](double num) {return num + average; });

	return numbers;
}