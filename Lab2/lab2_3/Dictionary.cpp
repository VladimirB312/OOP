#include "Dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary()
{
	fileName = "dictionary.txt";
}

Dictionary::Dictionary(const std::string& fileName)
	:fileName(fileName) {
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open file: " + fileName);
	}

	ParseFile(inputFile);
}

std::string Dictionary::ParseKey(const std::string& line, size_t& pos)
{
	std::string key;
	pos = line.find(":");
	if (pos == std::string::npos)
	{
		throw std::runtime_error("Failed to read word");
	}

	key.append(line, 0, pos);

	return key;
}

std::vector<std::string> Dictionary::ParseValues(const std::string& line, size_t& pos)
{
	std::vector<std::string> values;
	std::string value;
	while (++pos < line.size())
	{
		if (line[pos] == ';')
		{
			values.push_back(value);
			value.clear();
			continue;
		}
		value.push_back(line[pos]);
	}

	return values;
}

void Dictionary::ParseWord(const std::string& line)
{
	std::string key;
	std::vector<std::string> values;
	size_t pos;

	key = ParseKey(line, pos);
	values = ParseValues(line, pos);

	if (key.empty() || values.empty())
	{
		throw std::runtime_error("Failed to read word");
	}

	words[key] = values;
}

void Dictionary::ParseFile(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		ParseWord(line);
	}
}

void Dictionary::PrintTranslations(std::ostream& output, const std::string& query)
{
	for (const auto& word : words[query])
	{
		output << word << " ";
	}
	output << "\n";
}

void Dictionary::AddWord(std::istream& input, const std::string& query)
{	
	std::string translation;
	std::getline(input, translation);

	if (translation.empty())
	{
		std::cout << "Слово " << query << " проигнорировано.\n";
		return;
	}

	words[query].push_back(translation);
	isChanged = true;
}

void Dictionary::Request(std::istream& input, std::ostream& output, const std::string& query)
{
	if (query.empty())
	{
		return;
	}

	if (words.contains(query))
	{
		PrintTranslations(output, query);
		return;
	}

	output << "Неизвестное слово " << query << ". Введите перевод или пустую строку для отказа.\n";
	AddWord(input, query);
}

void Dictionary::Close()
{
	if (!isChanged)
	{
		return;
	}

	std::cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом.\n";
	char ch;
	std::cin >> ch;

	if (ch == 'Y' || ch == 'y')
	{
		SaveToFile();
	}
}

void Dictionary::SaveToFile()
{
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Error opening file to save");
	}

	for (const auto& [key, values] : words)
	{
		outputFile << key << ":";
		for (const auto& value : values)
		{
			outputFile << value << ";";
		}
		outputFile << "\n";
	}

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}

	std::cout << "Изменения сохранены. До свидания.";
}