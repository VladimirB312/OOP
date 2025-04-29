#include <iostream>
#include <string>
#include <vector>
#include "FindMax.h"

struct Sportsman
{
	std::string name;
	int height;
	int weight;
};

int main()
{
	std::vector<Sportsman> arrInt{
		{ "Alex", 175, 70 },
		{ "Viktor", 168, 73 },
		{ "Alexander", 182, 67 },
	};
	Sportsman maxWeight;
	Sportsman maxHeight;

	if (FindMax(arrInt, maxWeight, [](const Sportsman& s1, const Sportsman& s2) {
			return s1.weight < s2.weight;
		}))
	{
		std::cout << "sportsman name with max weight: " << maxWeight.name << "\n";
	}
	else
	{
		std::cout << "empty arr"
				  << "\n";
	}
	
	if (FindMax(arrInt, maxHeight, [](const Sportsman& s1, const Sportsman& s2) {
			return s1.height < s2.height;
		}))
	{
		std::cout << "sportsman name with max height: " << maxHeight.name << "\n";
	}
	else
	{
		std::cout << "empty arr"
				  << "\n";
	}

	return 0;
}
