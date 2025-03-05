#include "DictionaryWorker.h"
#include <fstream>
#include <iostream>

DictionaryWorker::DictionaryWorker(std::istream& input, std::ostream& output, Dictionary& dictionary)
	:input(input), output(output), dictionary(dictionary)
{

}

void DictionaryWorker::Start() 
{
	std::string word;
	while (getline(input, word))
	{
		if (word.empty())
		{
			continue;
		}

		if (word != "...")
		{
			RequestToDictionary(word);
			continue;
		}

		break;
	}
}

void DictionaryWorker::PrintTranslations(const std::vector<std::string>& translations)
{
	for (const auto& word : translations)
	{
		output << word << " ";
	}
	output << "\n";
}

void DictionaryWorker::ProcessUnknownWord(const std::string& word)
{
	output << "Ќеизвестное слово " << word << ". ¬ведите перевод или пустую строку дл€ отказа.\n";

	std::string translation;
	std::getline(input, translation);

	if (translation.empty())
	{
		output << "—лово " << word << " проигнорировано.\n";
		return;
	}

	dictionary.AddWord(word, translation);
	output << "—лово У" << word << "Ф сохранено в словаре как У" << translation << "Ф\n";
}

void DictionaryWorker::RequestToDictionary(const std::string& word)
{
	if (dictionary.IsInclude(word))
	{
		PrintTranslations(dictionary.GetTranslations(word));
		return;
	}

	ProcessUnknownWord(word);
}

bool DictionaryWorker::ShouldSaveChanges()
{
	if (!dictionary.WasChanged())
	{
		return false;
	}

	std::string answer;
	output << "¬ словарь были внесены изменени€.¬ведите Y или y дл€ сохранени€ перед выходом.\n";
	getline(input, answer);

	return answer == "Y" || answer == "y";
}

void DictionaryWorker::SaveDictionaryToFile(std::ostream& dictionaryFile)
{
	Entries entries = dictionary.GetAllEntries();
	for (const auto& [word, translations] : entries)
	{
		dictionaryFile << word << ":";
		
		for (const auto& translation : translations)
		{
			dictionaryFile << translation << ";";
		}
		dictionaryFile << "\n";
	}

	if (!dictionaryFile.flush())
	{
		throw std::runtime_error("Failed to save dictionary on file");
	}

	output << "»зменени€ сохранены. ƒо свидани€.";
}