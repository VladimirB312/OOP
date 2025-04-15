#include "CMystring.h"
#include <iostream>

int main()
{
	const CMyString str("hello");
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		std::cout << *it << " ";
	}

	std::cout << std::endl;

	for (const auto s : str)
	{
		std::cout << s;
	}

	
}
