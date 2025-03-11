#include "DictionaryWorker.h"
#include <fstream>
#include <iostream>

DictionaryWorker::DictionaryWorker(std::istream& input, std::ostream& output, Dictionary& dictionary)
	:m_input(input), m_output(output), m_dictionary(dictionary)
{

}

void DictionaryWorker::Start() 
{
	std::string word;
	while (getline(m_input, word))
	{
		if (word.empty())
		{
			continue;
		}

		if (word != "...")
		{
			TryToGetTranslation(word);
			continue;
		}

		break;
	}
}

void DictionaryWorker::PrintTranslations(const std::vector<std::string>& translations)
{
	for (const auto& word : translations)
	{
		m_output << word << " ";
	}
	m_output << "\n";
}

void DictionaryWorker::ProcessUnknownWord(const std::string& word)
{
	m_output << "����������� ����� " << word << ". ������� ������� ��� ������ ������ ��� ������.\n";

	std::string translation;
	std::getline(m_input, translation);

	if (translation.empty())
	{
		m_output << "����� " << word << " ���������������.\n";
		return;
	}

	m_dictionary.AddWord(word, translation);
	m_output << "����� �" << word << "� ��������� � ������� ��� �" << translation << "�\n";
}

void DictionaryWorker::TryToGetTranslation(const std::string& word)
{
	if (m_dictionary.IsInclude(word))
	{
		PrintTranslations(m_dictionary.GetTranslations(word));
		return;
	}

	ProcessUnknownWord(word);
}

bool DictionaryWorker::ShouldSaveChanges()
{
	if (!m_dictionary.WasChanged())
	{
		return false;
	}

	std::string answer;
	m_output << "� ������� ���� ������� ���������.������� Y ��� y ��� ���������� ����� �������.\n";
	getline(m_input, answer);

	return answer == "Y" || answer == "y";
}

void DictionaryWorker::SaveDictionaryToFile(std::ostream& dictionaryFile)
{
	Entries entries = m_dictionary.GetAllEntries();
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

	m_output << "��������� ���������. �� ��������.";
}