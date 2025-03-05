#pragma once
#include <sstream>
#include <vector>
#include "Dictionary.h"

class DictionaryWorker {
public:
	DictionaryWorker(std::istream& input, std::ostream& output, Dictionary& dictionary);
	void Start();
	void SaveDictionaryToFile(std::ostream& dictionaryFile);
	bool ShouldSaveChanges();
private:
	std::istream& input;
	std::ostream& output;
	Dictionary& dictionary;
	void PrintTranslations(const std::vector<std::string>& translations);
	void RequestToDictionary(const std::string& word);
	void ProcessUnknownWord(const std::string& word);
};