#include "ExpandTemplate.h"
#include "Replacer.h"
#include "StringTrimmer.h"
#include <fstream>
#include <iostream>

struct Pattern
{
	std::string key;
	std::string value;
};

Pattern ParsePattern(const std::string& line)
{
	size_t foundPos = line.find(":=");
	if (foundPos == std::string::npos)
	{
		throw std::runtime_error("Invalid input");
	}
	std::string key, value;
	key.append(line, 0, foundPos);
	value.append(line, foundPos + 2);

	return {
		Trim(key, ' '),
		Trim(value, ' ')
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

std::string GetReplacementString(std::istream& input)
{
	if (input.eof() || input.fail())
	{
		throw std::runtime_error("No template specified");
	}

	std::string replacementString;
	std::string line;
	bool isFirstLine = true;
	while (getline(input, line))
	{
		if (!isFirstLine)
		{
			replacementString.append("\n");
		}
		replacementString.append(line);
		isFirstLine = false;
	}

	return replacementString;
}

Patterns GetPatternsFromArgs(int argc, char* argv[])
{
	Patterns patterns;
	for (int i = 3; i < argc; i += 2)
	{
		std::string key = Trim(argv[i], '"');
		std::string value;
		if (i + 1 < argc)
		{
			value = Trim(argv[i + 1], '"');
		}

		if (patterns.contains(key))
		{
			throw std::invalid_argument("Non-unique key");
		}

		patterns[key] = value;
	}

	return patterns;
}

void CheckFile(std::ifstream& file)
{
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open input file");
	}
}

void CheckFile(std::ofstream& file)
{
	if (!file.is_open())
	{
		throw std::invalid_argument("Failed to open output file");
	}
}

void ExpandTemplateFromArgs(int argc, char* argv[])
{
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);
	CheckFile(input);
	CheckFile(output);

	Patterns patterns = GetPatternsFromArgs(argc, argv);
	Replacer replacer(patterns);

	std::string line;
	while (getline(input, line))
	{
		output << replacer.Replace(line) << "\n";
	}
}

void ExpandTemplateFromStream(std::istream& input, std::ostream& output)
{
	Patterns patterns = GetPatternsFromStream(input);
	std::string replacementString = GetReplacementString(input);
	Replacer replacer(patterns);
	output << replacer.Replace(replacementString);
}