#include <iostream>
#include <string>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			std::cout << "Url: " << url.GetURL() << "\n";
		}
		catch (const CUrlParsingError& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	return 0;
}
