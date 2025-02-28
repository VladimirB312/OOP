#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "HtmlDecode.h"

SCENARIO("Decoding empty string")
{
	REQUIRE(HtmlDecode("").empty());
}

SCENARIO("Decoding string without html entities")
{
	REQUIRE(HtmlDecode("string without html entities") == "string without html entities");
}

SCENARIO("Decoding a string containing only one html entity")
{
	REQUIRE(HtmlDecode("&quot;") == "\"");
}