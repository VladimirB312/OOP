#include "Dictionary.h"
#include <fstream>
#include <iostream>

Dictionary::Dictionary(const Entries& entries)
	:entries(entries)
{

}

Dictionary::Dictionary()	
{
}

Entries Dictionary::GetAllEntries()
{
	return entries;
}

bool Dictionary::WasChanged()
{
	return wasChanged;
}

void Dictionary::AddWord(const std::string& word, const std::string& translation)
{
	if (word.empty() || translation.empty())
	{
		return;
	}

	entries[word].push_back(translation);
	wasChanged = true;
}

bool Dictionary::IsInclude(const std::string& word)
{
	return entries.contains(word);
}

std::vector<std::string> Dictionary::GetTranslations(const std::string& word)
{
	if (!IsInclude(word))
	{
		throw std::runtime_error("Dictionary does not include " + word);
	}

	return entries[word];
}