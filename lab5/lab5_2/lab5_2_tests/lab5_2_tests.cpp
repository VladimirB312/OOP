#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyString.h"

SCENARIO("create string")
{
	WHEN("create string without parameters")
	{
		CMyString str;
		THEN("string should be an empty")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
		}
	}

	WHEN("create string with an empty string in parameters")
	{
		CMyString str("");
		THEN("string should be an empty")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
		}
	}

	WHEN("create string with one char in parameters")
	{
		CMyString str("a");
		THEN("string should contain only this char")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == "a");
		}
	}

	WHEN("create string with string hello in parameters")
	{
		CMyString str("hello");
		THEN("string should contain hello")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
		}
	}
}
