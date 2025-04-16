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

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		std::cout << *it << " ";
	}

	std::cout << std::endl;

	for (const auto s : str)
	{
		std::cout << s;
	}

	std::cout << std::endl;

	auto it = str.begin();
	auto it2 = 4 + it;
	std::cout << "it = " << *it << "\n";
	std::cout << "it2 = " << *it2 << "\n";

	std::cout << "dif = " << it2 - it << "\n";

	std::string newStr("12345");
	auto it3 = newStr.begin();
	std::cout << "it3 = " << it3[2];
}
