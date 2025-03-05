#include "EntriesParser.h"
#include <iostream>
#include <fstream>
#include <string>

std::string ParseWord(const std::string& line, size_t& pos)
{
	std::string word;
	pos = line.find(":");
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Failed to read word");
	}

	word.append(line, 0, pos);

	return word;
}

std::vector<std::string> ParseTranslations(const std::string& line, size_t& pos)
{
	std::vector<std::string> translations;
	std::string translation;
	while (++pos < line.size())
	{
		if (line[pos] == ';' && !translation.empty())
		{
			translations.push_back(translation);
			translation.clear();
			continue;
		}
		translation.push_back(line[pos]);
	}

	return translations;
}

void ParseEntrieFromString(const std::string& line, Entries& entries)
{
	std::string word;
	std::vector<std::string> translations;
	size_t pos;

	word = ParseWord(line, pos);
	translations = ParseTranslations(line, pos);

	if (word.empty() || translations.empty())
	{
		throw std::runtime_error("Failed to read word");
	}

	entries[word] = translations;
}

Entries ParseEntriesFromFile(std::istream& input)
{
	Entries entries;
	std::string line;
	while (std::getline(input, line))
	{
		ParseEntrieFromString(line, entries);
	}

	return entries;
}