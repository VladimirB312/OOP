#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Dictionary.h"

SCENARIO("Parse dictionary from file")
{
	Dictionary dictionary("test-data/Dictionary.txt");
	REQUIRE(dictionary.words["cat"][0] == "кошка");
	REQUIRE(dictionary.words["dog"][0] == "собака");
}

SCENARIO("Try to request empty word")
{
	Dictionary dictionary("test-data/Dictionary.txt");
	std::istringstream input("");
	dictionary.Request(input, std::cout, "meat");
	REQUIRE(!dictionary.words.contains("meat"));
}

SCENARIO("Add new word")
{
	Dictionary dictionary;
	std::istringstream input("мясо");
	dictionary.Request(input, std::cout, "meat");
	REQUIRE(dictionary.words["meat"][0] == "мясо");
}

SCENARIO("Print translation for existing word")
{
	Dictionary dictionary("test-data/Dictionary.txt");
	std::ostringstream output;
	dictionary.Request(std::cin, output, "english word");
	REQUIRE(output.str() == "russian word \n");
}

SCENARIO("Try to add empty translation")
{
	Dictionary dictionary;
	std::istringstream input("");
	dictionary.Request(input, std::cout, "meat");
	REQUIRE(!dictionary.words.contains("meat"));
}

SCENARIO("Add prase")
{
	Dictionary dictionary;
	std::istringstream input("Красная площадь");
	dictionary.Request(input, std::cout, "The Red Square");
	REQUIRE(dictionary.words["The Red Square"][0] == "Красная площадь");
}