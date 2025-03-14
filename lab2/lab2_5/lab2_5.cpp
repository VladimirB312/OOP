#include "ParseUrl.h"
#include <iostream>
#include <string>

int main()
{
	try
	{
		std::string line;
		while (getline(std::cin, line))
		{
			Url url = ParseUrl(line);
			std::cout << "\n"
					  << line << "\n";
			PrintUrl(std::cout, url);
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}
