#include <iostream>
#include <string>
#include "Replacer.h"
#include "ExpandTemplate.h"

int main(int argc, char* argv[])
{
	try {
		if (argc == 1)
		{
			Patterns patterns = GetPatternsFromStream(std::cin);
			std::vector<std::string> replacementStrings = GetReplacementStringsFromStream(std::cin);
			Replacer replacer(patterns);
			std::vector<std::string> expandedStrings = ReplaceMatchesInStrings(replacer, replacementStrings);
			PrintStrings(std::cout, expandedStrings);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
