#pragma once
#include "Replacer.h"

struct Pattern {
	std::string key;
	std::string value;
};

std::string TrimBlanks(const std::string& str);
Pattern ParsePattern(const std::string& line);
void AddPattern(Patterns& patterns, const std::string& line);
Patterns GetPatternsFromStream(std::istream& input);
std::vector<std::string> GetReplacementStringsFromStream(std::istream& input);
std::vector<std::string> ReplaceMatchesInStrings(Replacer& replacer, const std::vector<std::string>& replacementStrings);
void PrintStrings(std::ostream& output, const std::vector<std::string>& strings);