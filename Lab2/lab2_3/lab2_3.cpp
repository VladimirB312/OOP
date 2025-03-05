#include <iostream>
#include <fstream>
#include <windows.h>
#include "Dictionary.h"
#include "DictionaryWorker.h"
#include "EntriesParser.h"

Dictionary CreateDictionary(int argc, char* argv[])
{
	if (argc == 1)
	{
		return Dictionary();
	}

	if (argc == 2)
	{
		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			throw std::invalid_argument("Failed to open file " + std::string(argv[1]));
		}

		return Dictionary(ParseEntriesFromFile(inputFile));
	}

	throw std::invalid_argument("Invaild argument");
}

void StartWork(DictionaryWorker& dictionaryWorker, const std::string& dictionaryFileName)
{
	dictionaryWorker.Start();

	if (!dictionaryWorker.ShouldSaveChanges())
	{
		return;
	}

	std::ofstream dictionaryFile(dictionaryFileName);
	if (!dictionaryFile.is_open())
	{
		throw std::runtime_error("Failed to open file " + dictionaryFileName);
	}

	dictionaryWorker.SaveDictionaryToFile(dictionaryFile);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	//system("chcp 1251");

	try {
		std::string dictionaryFileName = argc == 2 ? argv[1] : "new_dictionary.txt";
		Dictionary dictionary = CreateDictionary(argc, argv);
		DictionaryWorker dictionaryWorker(std::cin, std::cout, dictionary);
		StartWork(dictionaryWorker, dictionaryFileName);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return 1;
	}

	return 0;
}