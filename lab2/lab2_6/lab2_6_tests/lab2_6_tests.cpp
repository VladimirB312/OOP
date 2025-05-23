﻿#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../ExpandTemplate.h"
#include "../Replacer.h"

SCENARIO("Replace string")
{
	WHEN("replacement string is empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be an empty")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("");
			CHECK(result.empty());
		}
	}

	WHEN("replacement string is empty and the pattern is not empty")
	{
		Patterns patterns = {
			{ { "dog" }, { "cat" } }
		};
		THEN("the result string must be an empty")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("");
			CHECK(result.empty());
		}
	}

	WHEN("replacement string is not empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be unchanged")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			CHECK(result == "cat and dog");
		}
	}

	WHEN("pattern not contain key")
	{
		Patterns patterns = {
			{ {}, { "cat" } }
		};
		THEN("the result string must be unchanged")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			REQUIRE(result == "cat and dog");
		}
	}

	WHEN("replacement string contain pattern string but pattern key not contain value")
	{
		Patterns patterns = {
			{ { "and" }, {} },
		};
		THEN("the result string must be replaced with an empty string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			REQUIRE(result == "cat  dog");
		}
	}

	WHEN("replacement string contain pattern string at the end of string")
	{
		Patterns patterns = {
			{ { "dog" }, { "cat" } }
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			CHECK(result == "cat and cat");
		}
	}

	WHEN("replacement string contain pattern string at the begining of string")
	{
		Patterns patterns = {
			{ { "dog" }, { "cat" } }
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("dog and cat");
			CHECK(result == "cat and cat");
		}
	}

	WHEN("replacement string contains part of a pattern"
		 "and the pattern itself is included in this string")
	{
		Patterns patterns = {
			{ { "1231234" }, { "XYZ" } }
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("12312312345");
			CHECK(result == "123XYZ5");
		}
	}

	WHEN("replacement string contains multiple occureances of a pattern")
	{
		Patterns patterns = {
			{ { "ma" }, { "mama" } }
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("mama delala pelmeni");
			CHECK(result == "mamamama delala pelmeni");
		}
	}

	WHEN("replacement string contains several patterns")
	{
		Patterns patterns = {
			{ { "cat" }, { "fox" } },
			{ { "dog" }, { "bear" } }
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			REQUIRE(result == "fox and bear");
		}
	}

	WHEN("replacement string contains multiple occureances of a pattern and patterns contains subpattern")
	{
		Patterns patterns = {
			{ { "ma" }, { "mama" } },
			{ { "masha" }, { "dasha" } }
		};
		THEN("the result string must be replaced with a longher pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("masha delala pelmeni");
			REQUIRE(result == "dasha delala pelmeni");
		}
	}

	WHEN("replacement string contains several possible substitution options")
	{
		Patterns patterns = {
			{ { "A" }, { "[a]" } },
			{ { "AA" }, { "[aa]" } },
			{ { "B" }, { "[b]" } },
			{ { "BB" }, { "[bb]" } },
			{ { "C" }, { "[c]" } },
			{ { "CC" }, { "[cc]" } }
		};

		THEN("the result string must be replaced with the longest option is selected")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("-AABBCCCCCABC+");
			CHECK(result == "-[aa][bb][cc][cc][c][a][b][c]+");
		}
	}
}

SCENARIO("ExpandTemplateFromStream")
{
	WHEN("input contains empty patterns")
	{
		std::istringstream input("\n"
								 "Hello, %USER_NAME%.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("the output should be unchanged")
		{
			CHECK(output.str() == "Hello, %USER_NAME%.");
		}
	}

	WHEN("input contains empty patterns key")
	{
		std::istringstream input(" := Bye\n"
								 "\n"
								 "Hello, %USER_NAME%.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("the key should be ignored")
		{
			CHECK(output.str() == "Hello, %USER_NAME%.");
		}
	}

	WHEN("input contains pattern with a non-unique key")
	{
		std::istringstream input("Hello := Bye\n"
								 "Hello := Goodbye\n"
								 "\n"
								 "Hello, %USER_NAME%.\n");

		std::ostringstream output;

		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(ExpandTemplateFromStream(input, output), std::runtime_error);
		}
	}

	WHEN("input not contains a whitespaces between pattern key and value")
	{
		std::istringstream input("Hello:=Bye\n"
								 "\n"
								 "Hello, %USER_NAME%.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("whitespaces should be ignored")
		{
			CHECK(output.str() == "Bye, %USER_NAME%.");
		}
	}

	WHEN("input contains empty patterns values")
	{
		std::istringstream input("%USER_NAME% :=\n"
								 "{WEEK_DAY} :=\n"
								 "\n"
								 "Hello, %USER_NAME%.\n"
								 "Today is {WEEK_DAY}.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("matches values are replaced with empty string")
		{
			CHECK(output.str() == "Hello, .\nToday is .");
		}
	}

	WHEN("input contains patterns with nested parameters")
	{
		std::istringstream input("%USER_NAME% := Super %USER_NAME% {WEEK_DAY}\n"
								 "{WEEK_DAY} := Friday. {WEEK_DAY}\n"
								 "\n"
								 "Hello, %USER_NAME%.\n"
								 "Today is {WEEK_DAY}.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("parameters in substitution values are not re-evaluated")
		{
			CHECK(output.str() == "Hello, Super %USER_NAME% {WEEK_DAY}.\nToday is Friday. {WEEK_DAY}.");
		}
	}

	WHEN("input contains patterns with nested parameters")
	{
		std::istringstream input("%USER_NAME% := Super %USER_NAME% {WEEK_DAY}\n"
								 "{WEEK_DAY} := Friday. {WEEK_DAY}\n"
								 "\n"
								 "Hello, %USER_NAME%.\n"
								 "Today is {WEEK_DAY}.\n");

		std::ostringstream output;
		ExpandTemplateFromStream(input, output);

		THEN("parameters in substitution values are not re-evaluated")
		{
			CHECK(output.str() == "Hello, Super %USER_NAME% {WEEK_DAY}.\nToday is Friday. {WEEK_DAY}.");
		}
	}

	WHEN("input not contains text to replace")
	{
		std::istringstream input("%USER_NAME% := Ivan Petrov\n"
								 "{WEEK_DAY} := Friday\n");

		std::ostringstream output;

		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(ExpandTemplateFromStream(input, output), std::runtime_error);
		}
	}
}