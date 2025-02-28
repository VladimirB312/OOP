#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Dictionary.h"

Dictionary ParseArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		return Dictionary();
	}

	if (argc == 2)
	{
		return Dictionary(argv[1]);
	}

	throw std::invalid_argument("Invaild argument");
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	try {
		Dictionary dictionary = ParseArgs(argc, argv);

		std::string query;
		while (getline(std::cin, query))
		{		
			if (query != "...")
			{
				dictionary.Request(std::cin, std::cout, query);
				continue;
			}

			dictionary.Close();
			break;
		}
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}


	return 0;
}