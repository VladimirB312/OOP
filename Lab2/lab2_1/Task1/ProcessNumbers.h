#pragma once
#include <vector>
#include <iosfwd>

std::vector<double> ReadNumbers(std::istream& input);

void PrintSortedNumbers(std::ostream& output, std::vector<double> numbers);

std::vector<double> ProcessNumbers(std::vector<double>& numbers);