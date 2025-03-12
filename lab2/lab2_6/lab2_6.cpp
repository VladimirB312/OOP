#include <iostream>
#include <windows.h>
#include "Replacer.h"
#include "ExpandTemplate.h"

bool NeedHelp(int argc, char* argv[])
{
	return argc == 2 && argv[1] == "-h";
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try {
		if (NeedHelp(argc, argv))
		{
			std::cout << "Usage: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> ...]]";
			return 0;
		}
		if (argc == 1)
		{
			ExpandTemplateFromStream(std::cin, std::cout);
			return 0;
		}
		if (argc > 2)
		{
			ExpandTemplateFromArgs(argc, argv);
			return 0;
		}

		throw std::invalid_argument("Invalid argument count. Usage: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> ...]]");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();

		return 1;
	}

	return 0;
}
