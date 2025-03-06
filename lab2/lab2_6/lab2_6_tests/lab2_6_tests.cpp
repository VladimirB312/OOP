#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Replacer.h"

SCENARIO("Replace string")
{
	WHEN("replacement string is empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be an empty")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("");
			REQUIRE(result.empty());
		}
	}

	WHEN("replacement string is empty and the pattern is not empty")
	{
		Patterns patterns = {
			{{"dog"}, {"cat"}}
		};
		THEN("the result string must be an empty")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("");
			REQUIRE(result.empty());
		}
	}

	WHEN("replacement string is not empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be unchanged")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("cat and dog");
			REQUIRE(result == "cat and dog");
		}
	}

	WHEN("replacement string contain pattern string at the end of string")
	{
		Patterns patterns = {
			{{"dog"}, {"cat"}}
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("cat and dog");
			REQUIRE(result == "cat and cat");
		}
	}

	WHEN("replacement string contain pattern string at the begining of string")
	{
		Patterns patterns = {
			{{"dog"}, {"cat"}}
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("dog and cat");
			REQUIRE(result == "cat and cat");
		}
	}

	WHEN("replacement string contains part of a pattern"
		"and the pattern itself is included in this string")
	{
		Patterns patterns = {
			{{"1231234"}, {"XYZ"}}
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("12312312345");
			REQUIRE(result == "123XYZ5");
		}
	}

	WHEN("replacement string contains multiple occureances of a pattern")
	{
		Patterns patterns = {
			{{"ma"}, {"mama"}}
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.ReplaceMatches("mama delala pelmeni");
			REQUIRE(result == "mamamama delala pelmeni");
		}
	}
}
