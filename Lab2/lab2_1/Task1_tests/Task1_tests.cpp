#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "ProcessNumbers.h"

SCENARIO("Read numbers")
{
	WHEN("input stream is empty")
	{
		std::istringstream input("");
		THEN("vector is also empty")
		{
			std::vector<double> numbers = ReadNumbers(input);
			CHECK(numbers.empty());
		}
	}

	WHEN("input stream contains one number")
	{
		std::istringstream input("56");
		std::vector<double> number = ReadNumbers(input);

		THEN("vector contains one number") {

			CHECK(number.size() == 1);
		}
		AND_THEN("the first number in the vector is the input number")
		{
			CHECK(number[0] == 56);
		}
	}

	WHEN("input stream contains 3 numbers")
	{
		std::istringstream input("123 14 23");
		std::vector<double> number = ReadNumbers(input);

		THEN("vector contains 3 numbers") {

			CHECK(number.size() == 3);
		}
		AND_THEN("numbers in vector equal to input numbers")
		{
			CHECK(number[0] == 123);
			CHECK(number[1] == 14);
			CHECK(number[2] == 23);
		}
	}

	WHEN("input stream contains not a number")
	{
		THEN("vector contains 3 numbers") {
			std::istringstream input("a");
			CHECK_THROWS_AS(ReadNumbers(input), std::runtime_error);
		}
	}
}


SCENARIO("Print sorted numbers")
{
	std::ostringstream output;

	WHEN("vector is empty")
	{
		std::vector<double> numbers;
		THEN("output stream is also empty")
		{
			PrintSortedNumbers(output, numbers);
			CHECK(output.str().empty());
		}
	}

	WHEN("vector contains one number")
	{
		std::vector<double> numbers{ 1 };
		THEN("output stream contains this one number")
		{
			PrintSortedNumbers(output, numbers);
			CHECK(output.str() == "1.000");
		}
	}

	WHEN("vector contains 3 sorted number")
	{
		std::vector<double> numbers{ 1, 2, 3 };
		THEN("output stream contains these 3 number in sorted order")
		{
			PrintSortedNumbers(output, numbers);
			CHECK(output.str() == "1.000 2.000 3.000");
		}
	}

	WHEN("vector contains 3 unsorted number")
	{
		std::vector<double> numbers{ 3, 2, 1 };
		THEN("output stream contains these 3 number in sorted order")
		{
			PrintSortedNumbers(output, numbers);
			CHECK(output.str() == "1.000 2.000 3.000");
		}
	}
}

SCENARIO("Add to each array element the arithmetic mean of its positive elements")
{
	std::vector<double> result;

	WHEN("vector is empty")
	{
		std::vector<double> numbers;
		THEN("result vector is also empty")
		{
			result = ProcessNumbers(numbers);
			CHECK(result.empty());
		}
	}

	WHEN("vector contains 1 positive number")
	{
		std::vector<double> numbers{ 5 };
		THEN("result vector contains twice this number")
		{
			result = ProcessNumbers(numbers);
			CHECK(result[0] == 10.0);
		}
	}

	WHEN("vector contains 1 negative number")
	{
		std::vector<double> numbers{ -5 };
		THEN("result vector contains this number")
		{
			result = ProcessNumbers(numbers);
			CHECK(result[0] == -5.0);
		}
	}

	WHEN("vector contains number == 0")
	{
		std::vector<double> numbers{ 0 };
		THEN("result vector contains number == 0")
		{
			result = ProcessNumbers(numbers);
			CHECK(result[0] == 0.0);
		}
	}

	WHEN("vector contains only positive numbers")
	{
		std::vector<double> numbers{ 1, 2, 3, 4 };

		THEN("result contains numbers with arithmetic mean")
		{
			result = ProcessNumbers(numbers);
			CHECK_THAT(result[0], Catch::Matchers::WithinAbs(3.5, 0.001));
			CHECK_THAT(result[1], Catch::Matchers::WithinAbs(4.5, 0.001));
			CHECK_THAT(result[2], Catch::Matchers::WithinAbs(5.5, 0.001));
			CHECK_THAT(result[3], Catch::Matchers::WithinAbs(6.5, 0.001));
		}
	}

	WHEN("vector contains only negative numbers")
	{
		std::vector<double> numbers{ -1.4, -703, -3.6, -11.0 };
		THEN("result contains same numbers")
		{
			result = ProcessNumbers(numbers);
			CHECK_THAT(result[0], Catch::Matchers::WithinAbs(-1.4, 0.001));
			CHECK_THAT(result[1], Catch::Matchers::WithinAbs(-703, 0.001));
			CHECK_THAT(result[2], Catch::Matchers::WithinAbs(-3.6, 0.001));
			CHECK_THAT(result[3], Catch::Matchers::WithinAbs(-11.0, 0.001));
		}
	}
}

SCENARIO("Read and print processed sorted result")
{
	std::ostringstream output;

	WHEN("input stream contains only positive numbers")
	{
		std::istringstream input("1.0 2 3.659512");
		std::vector<double> numbers = ReadNumbers(input);

		THEN("output stream contains processed sorted numbers")
		{
			numbers = ProcessNumbers(numbers);
			PrintSortedNumbers(output, numbers);
			CHECK(output.str() == "3.220 4.220 5.879");
		}
	}

	WHEN("input stream contains only negative numbers")
	{
		std::istringstream input("-1.0004000 -703 -3.659512 -11");
		std::vector<double> numbers = ReadNumbers(input);

		THEN("output stream contains processed sorted numbers")
		{
			numbers = ProcessNumbers(numbers);
			PrintSortedNumbers(output, numbers);
			CHECK(output.str() == "-703.000 -11.000 -3.660 -1.000");
		}
	}
}