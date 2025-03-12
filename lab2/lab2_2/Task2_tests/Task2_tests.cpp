#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "Replacer.h"
#include "HtmlDecode.h"

SCENARIO("Replace string")
{
	WHEN("replacement string is empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be an empty")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("");
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
			std::string result = replacer.Replace("");
			REQUIRE(result.empty());
		}
	}

	WHEN("replacement string is not empty and the pattern is empty")
	{
		Patterns patterns = {};
		THEN("the result string must be unchanged")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
			REQUIRE(result == "cat and dog");
		}
	}

	WHEN("pattern not contain key")
	{
		Patterns patterns = {
			{{}, {"cat"}}
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
			{{"and"}, {}},
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
			{{"dog"}, {"cat"}}
		};
		THEN("the result string must be replaced with a pattern string")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("cat and dog");
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
			std::string result = replacer.Replace("dog and cat");
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
			std::string result = replacer.Replace("12312312345");
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
			std::string result = replacer.Replace("mama delala pelmeni");
			REQUIRE(result == "mamamama delala pelmeni");
		}
	}

	WHEN("replacement string contains several patterns")
	{
		Patterns patterns = {
			{{"cat"}, {"fox"}},
			{{"dog"},{"bear"}}
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
			{{"ma"}, {"mama"}},
			{{"masha"},{"dasha"}}
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
			{{"A"}, {"[a]"}},
			{{"AA"}, {"[aa]"}},
			{{"B"}, {"[b]"}},
			{{"BB"}, {"[bb]"}},
			{{"C"}, {"[c]"}},
			{{"CC"}, {"[cc]"}}
		};

		THEN("the result string must be replaced with the longest option is selected")
		{
			Replacer replacer(patterns);
			std::string result = replacer.Replace("-AABBCCCCCABC+");
			CHECK(result == "-[aa][bb][cc][cc][c][a][b][c]+");
		}
	}
}

SCENARIO("Html decode")
{
	std::ostringstream output;

	WHEN("input stream is empty")
	{
		THEN("output must should be empty too")
		{
			std::istringstream input("");
			HtmlDecode(input, output);
			REQUIRE(output.str().empty());
		}
	}

	WHEN("input stream contains no entities")
	{
		THEN("output must be equal to input")
		{
			std::istringstream input("some text");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "some text");
		}
	}

	WHEN("input stream contains entity at the beginning of the stream")
	{
		THEN("output must be decoded")
		{
			std::istringstream input("&apos; some text");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "' some text");
		}
	}

	WHEN("input stream contains entity at the end of the stream")
	{
		THEN("output must be decoded")
		{
			std::istringstream input("some text &apos;");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "some text '");
		}
	}

	WHEN("input stream contains entity at the middle of the stream")
	{
		THEN("output must be decoded")
		{
			std::istringstream input("some &apos; text");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "some ' text");
		}
	}

	WHEN("input stream contains all entities")
	{
		THEN("output must be decoded")
		{
			std::istringstream input("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
			HtmlDecode(input, output);
			REQUIRE(output.str() == "Cat <says> \"Meow\". M&M's");
		}
	}
}