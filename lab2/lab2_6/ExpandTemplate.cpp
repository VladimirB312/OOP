#include "ExpandTemplate.h"
#include <iostream>

std::string TrimBlanks(const std::string& str)
{
	std::string result;
	size_t start = str.find_first_not_of(" ");
	if (start == std::string::npos)
	{
		return result;
	}

	size_t finish = str.find_last_not_of(" ");
	result.append(str, start, finish - start + 1);

	return result;
}

Pattern ParsePattern(const std::string& line)
{
	size_t foundPos = line.find(":=");
	if (foundPos == std::string::npos)
	{
		throw std::runtime_error("Invalid pattern format");
	}
	std::string key, value;
	key.append(line, 0, foundPos);
	value.append(line, foundPos + 2);

	return {
		TrimBlanks(key),
		TrimBlanks(value)
	};
}

void AddPattern(Patterns& patterns, const std::string& line)
{
	Pattern pattern = ParsePattern(line);
	if (pattern.key.empty())
	{
		return;
	}
	if (patterns.contains(pattern.key))
	{
		throw std::runtime_error("Non-unique key");
	}
	patterns[pattern.key] = pattern.value;
}

Patterns GetPatternsFromStream(std::istream& input)
{
	Patterns patterns;
	std::string line;
	while (getline(input, line) && !line.empty())
	{
		AddPattern(patterns, line);
	}

	return patterns;
}


std::vector<std::string> GetReplacementStringsFromStream(std::istream& input)
{
	if (input.eof())
	{
		throw std::runtime_error("No template specified");
	}

	std::vector<std::string> replacementStrings;
	std::string line;
	while (getline(input, line))
	{
		replacementStrings.push_back(line);
	}

	return replacementStrings;
}

std::vector<std::string> ReplaceMatchesInStrings(Replacer& replacer, const std::vector<std::string>& replacementStrings)
{
	std::vector<std::string> result;
	for (const auto& string : replacementStrings)
	{
		result.push_back(replacer.ReplaceMatches(string));
	}

	return result;
}

void PrintStrings(std::ostream& output, const std::vector<std::string>& strings)
{
	for (int i = 0; i < strings.size(); i++)
	{
		if (i != 0)
		{
			output << "\n";
		}
		output << strings[i];
	}
}