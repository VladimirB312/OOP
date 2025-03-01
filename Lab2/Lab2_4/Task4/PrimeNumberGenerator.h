#pragma once
#include <set>
#include <fstream>
#include <vector>

const int MIN_NUMBER_COUNT = 2;
const int MAX_NUMBER_COUNT = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers);
std::vector<bool> GeneratePrimeNumberBoolVector(int upperBound);