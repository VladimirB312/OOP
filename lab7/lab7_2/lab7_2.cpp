#include <iostream>
#include "MyArray.h"

int main()
{
	MyArray<int> arr;
	arr.Push(1);
	arr.Push(2);
	arr.Push(3);

	MyArray<double> arr2;
	arr2.Push(1.4);
	arr2.Push(2.3);
	arr2.Push(5.2);
	arr = arr2;
	for (auto it = arr.rbegin(); it != arr.rend(); ++it)
	{
		std::cout << *it;
	}
}
