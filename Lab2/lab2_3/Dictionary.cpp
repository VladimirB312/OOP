#include "Dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary(const Entries& entries)
	:m_entries(entries)
{

}

Dictionary::Dictionary()	
{
}

Entries Dictionary::GetAllEntries()
{
	return m_entries;
}

bool Dictionary::WasChanged()
{
	return m_wasChanged;
}

void Dictionary::AddWord(const std::string& word, const std::string& translation)
{
	if (word.empty() || translation.empty())
	{
		return;
	}

	m_entries[word].push_back(translation);
	m_wasChanged = true;
}

bool Dictionary::IsInclude(const std::string& word)
{
	return m_entries.contains(word);
}

std::vector<std::string> Dictionary::GetTranslations(const std::string& word)
{
	if (!IsInclude(word))
	{
		throw std::runtime_error("Dictionary does not include " + word);
	}

	return m_entries[word];
}