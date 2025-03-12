#pragma once
#include <set>
#include <fstream>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers);