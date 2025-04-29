#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMax.h"
#include <functional>
#include <vector>
SCENARIO("test int array")
{
	WHEN("array is empty")
	{
		std::vector<int> arr;
		THEN("function should return false and not change the passed value")
		{
			int value = 0;
			CHECK(FindMax(arr, value, std::less<>()) == false);
			CHECK(value == 0);
		}
	}

	WHEN("array contains 1 element")
	{
		std::vector<int> arr{ 5 };
		THEN("function should return true and write the value")
		{
			int value = 0;
			CHECK(FindMax(arr, value, std::less<>()) == true);
			CHECK(value == 5);
		}
	}

	WHEN("array contains 2 elements in ascending order")
	{
		std::vector<int> arr{ 5, 7 };
		THEN("function should return true and write the value of the larger one")
		{
			int value = 0;
			CHECK(FindMax(arr, value, std::less<>()) == true);
			CHECK(value == 7);
		}
	}

	WHEN("array contains 2 elements in descending order")
	{
		std::vector<int> arr{ 7, 5 };
		THEN("function should return true and write the value of the larger one")
		{
			int value = 0;
			CHECK(FindMax(arr, value, std::less<>()) == true);
			CHECK(value == 7);
		}
	}

	WHEN("array contains 10 elements in different order, the function should return true and write the value of the larger one")
	{
		std::vector<int> arr{ 3, 8, 1, 11, 2, 14, 7, 5, 4, 9 };
		THEN("function should return true and write the value of the larger one")
		{
			int value = 0;
			CHECK(FindMax(arr, value, std::less<>()) == true);
			CHECK(value == 14);
		}
	}
}

SCENARIO("test sportsmen")
{
	struct Sportsman
	{
		std::string name;
		int height;
		int weight;
	};

	auto heightCmp = [](const Sportsman& s1, const Sportsman& s2) { return s1.height < s2.height; };
	auto weightCmp = [](const Sportsman& s1, const Sportsman& s2) { return s1.weight < s2.weight; };

	WHEN("array is empty")
	{
		std::vector<Sportsman> arr;
		Sportsman s{ "s", 0, 0 };
		THEN("weight comparison function should return false and not change the passed value")
		{

			CHECK(FindMax(arr, s, weightCmp) == false);
			CHECK(s.weight == 0);
		}

		AND_THEN("height comparison function should return false and not change the passed value")
		{
			CHECK(FindMax(arr, s, heightCmp) == false);
			CHECK(s.height == 0);
		}
	}

	WHEN("array contains 1 element")
	{
		std::vector<Sportsman> arr{ { "Alex", 170, 70 } };
		Sportsman s{ "s", 0, 0 };
		THEN("weight comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, heightCmp) == true);
			CHECK(s.height == 170);
			CHECK(s.name == "Alex");
		}
		AND_THEN("height comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, weightCmp) == true);
			CHECK(s.weight == 70);
			CHECK(s.name == "Alex");
		}
	}

	WHEN("array contains 2 elements in ascending order")
	{
		std::vector<Sportsman> arr{ { "Alex", 170, 70 }, { "Viktor", 175, 75 } };
		Sportsman s{ "s", 0, 0 };
		THEN("weight comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, heightCmp) == true);
			CHECK(s.height == 175);
			CHECK(s.name == "Viktor");
		}
		AND_THEN("height comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, weightCmp) == true);
			CHECK(s.weight == 75);
			CHECK(s.name == "Viktor");
		}
	}

	WHEN("array contains 2 elements in descending order")
	{
		std::vector<Sportsman> arr{ { "Viktor", 175, 75 }, { "Alex", 170, 70 } };
		Sportsman s{ "s", 0, 0 };
		THEN("weight comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, heightCmp) == true);
			CHECK(s.height == 175);
			CHECK(s.name == "Viktor");
		}
		AND_THEN("height comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, weightCmp) == true);
			CHECK(s.weight == 75);
			CHECK(s.name == "Viktor");
		}
	}

	WHEN("array contains 3 elements in different order, the function should return true and write the value of the larger one")
	{
		std::vector<Sportsman> arr{ { "Viktor", 175, 75 }, { "Alex", 170, 70 }, { "Fedor", 182, 65 } };
		Sportsman s{ "s", 0, 0 };

		THEN("weight comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, heightCmp) == true);
			CHECK(s.height == 182);
			CHECK(s.name == "Fedor");
		}
		AND_THEN("height comparison function should return true and write the value")
		{
			CHECK(FindMax(arr, s, weightCmp) == true);
			CHECK(s.weight == 75);
			CHECK(s.name == "Viktor");
		}
	}
}