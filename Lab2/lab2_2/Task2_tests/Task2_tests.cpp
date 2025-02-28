#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "Replacer.h"

Patterns patterns = {
		{{"&quot;" }, { "\"" }},
		{{"&apos;"},{"\'"}},
		{{"&lt;"},{"<"}},
		{{"&gt;"},{">"}},
		{{"&amp;"},{"&"}}
};

AhoReplacer replacer(patterns);

SCENARIO("Replace on empty string")
{
	REQUIRE(replacer.ReplaceMatches("") == "");
}

SCENARIO("Replacement in a string that does not contain an entity")
{
	REQUIRE(replacer.ReplaceMatches("not contain an entity") == "not contain an entity");
}

SCENARIO("Replacement in a string containing part of an entity")
{
	REQUIRE(replacer.ReplaceMatches("contain part &qu entity") == "contain part &qu entity");
}

SCENARIO("Replacement in a line containing an entity at the beginning of the line")
{
	REQUIRE(replacer.ReplaceMatches("&apos; contain entity") == "' contain entity");
}

SCENARIO("Replacement in a string containing an entity at the end of the string")
{
	REQUIRE(replacer.ReplaceMatches("contain entity &apos;") == "contain entity '");
}

SCENARIO("Replacement in a line containing an entity at the beginning of the line after a space")
{
	REQUIRE(replacer.ReplaceMatches(" &apos; contain entity") == " ' contain entity");
}

SCENARIO("Replacement in a line containing an entity at the end of the line before a space")
{
	REQUIRE(replacer.ReplaceMatches("contain entity &apos; ") == "contain entity ' ");
}

SCENARIO("Replacement in a line containing an entity in the middle")
{
	REQUIRE(replacer.ReplaceMatches("contain entity &apos; contain entity") == "contain entity ' contain entity");
}

SCENARIO("Replacement in a line containing all entities")
{
	REQUIRE(replacer.ReplaceMatches("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
}