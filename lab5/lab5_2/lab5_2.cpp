#include <iostream>
#include "CMystring.h"
int main()
{
	CMyString str = "Hello world!";
    std::cout << str.SubString(1, 1).GetStringData();
}
