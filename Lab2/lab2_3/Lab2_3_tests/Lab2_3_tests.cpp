#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Dictionary.h"
#include "../EntriesParser.h"
#include "../DictionaryWorker.h"

SCENARIO("Parse entries from file")
{
	WHEN("file is empty")
	{
		std::istringstream input("");
		Entries entries = ParseEntriesFromFile(input);
		THEN("entries should be empty too")
		{
			REQUIRE(entries.empty());
		}
	}

	WHEN("file contains an empty key")
	{
		std::istringstream input(":value");
		THEN("entries must be empty too")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains an empty value")
	{
		std::istringstream input("key:");
		THEN("entries must be empty too")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains an empty value")
	{
		std::istringstream input("key:");
		THEN("throws runtime error")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains an entrie of the wrong format")
	{
		std::istringstream input("key,value");
		THEN("throws runtime error")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains an entrie of the wrong format")
	{
		std::istringstream input("key,value;");
		THEN("throws runtime error")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains an entrie of the wrong format")
	{
		std::istringstream input("key:;");
		THEN("throws runtime error")
		{
			REQUIRE_THROWS_AS(ParseEntriesFromFile(input), std::runtime_error);
		}
	}

	WHEN("file contains correct entries")
	{
		std::istringstream input("key:value1;value2;value3;");
		Entries entries = {
				{"key", {"value1", "value2", "value3"}}
		};
		THEN("entries must matches entries in the file")
		{
			REQUIRE(entries == ParseEntriesFromFile(input));
		}
	}

	WHEN("file contains correct entries from phrases")
	{
		std::istringstream input("key one:value1 value2;");
		Entries entries = {
				{"key one", {"value1 value2"}}
		};
		THEN("entries must matches entries in the file")
		{
			REQUIRE(entries == ParseEntriesFromFile(input));
		}
	}
}

SCENARIO("Create dictionary from file")
{
	WHEN("file is empty")
	{
		std::istringstream input("");
		Dictionary dictionary(ParseEntriesFromFile(input));
		THEN("dictionary should be empty too")
		{
			REQUIRE(dictionary.GetAllEntries().empty());
		}
	}

	WHEN("file contains correct entries")
	{
		std::istringstream input("key1:value1_1;value1_2;\nkey2:value2_1;value2_2;");
		Entries entries = {
				{"key1", {"value1_1", "value1_2"}},
				{"key2", {"value2_1", "value2_2"}}
		};
		Dictionary dictionary(ParseEntriesFromFile(input));
		THEN("dictionary's entries must matches entries in the file")
		{

			REQUIRE(entries == dictionary.GetAllEntries());
		}
	}
}

SCENARIO("Add and read entry in dictionary")
{
	std::istringstream input("cat:кошка;");

	WHEN("request translations of an existing word")
	{
		Dictionary dictionary(ParseEntriesFromFile(input));
		THEN("dictionary should return translations of the word")
		{
			REQUIRE(dictionary.GetTranslations("cat")[0] == "кошка");
		}
	}

	WHEN("request a non-existent word")
	{
		Dictionary dictionary;
		THEN("throws runtime error")
		{
			REQUIRE_THROWS_AS(dictionary.GetTranslations("dog"), std::runtime_error);
		}
	}

	WHEN("add a translation for a new empty word")
	{
		Dictionary dictionary;
		dictionary.AddWord("", "кошка");
		THEN("dictionary should not contain this word")
		{
			REQUIRE(!dictionary.IsInclude("cat"));
		}
	}

	WHEN("add an empty translation for a new word")
	{
		Dictionary dictionary;
		dictionary.AddWord("cat", "");
		THEN("dictionary should not contain this word")
		{
			REQUIRE(!dictionary.IsInclude("cat"));
		}
	}

	WHEN("add a correct translation for a correct new word")
	{
		Dictionary dictionary;
		dictionary.AddWord("cat", "кошка");
		THEN("dictionary should contain this word")
		{
			REQUIRE(dictionary.IsInclude("cat"));
		}
		AND_THEN("dictionary should contain a translation of this word")
		{
			REQUIRE(dictionary.GetTranslations("cat")[0] == "кошка");
		}
	}
}