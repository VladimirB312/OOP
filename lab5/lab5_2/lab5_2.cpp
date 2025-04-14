#include "CMystring.h"
#include <iostream>

int main()
{
	CMyString str("hello", 6);
	CMyString str2("world");
	str += str2;
	std::cout << str.GetLength() << "\n";
	std::cout << str.GetStringData() << "\n";
	std::cout << str.SubString(6, 10).GetStringData();
}
