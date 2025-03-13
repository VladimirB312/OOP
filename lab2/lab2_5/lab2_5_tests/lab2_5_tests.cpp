#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../ParseUrl.h"

SCENARIO("Parse invalid url")
{
	WHEN("input string is empty")
	{
		std::string input = "";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string does not conatin a protocol")
	{
		std::string input = "google.com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string does not conatin a protocol name")
	{
		std::string input = "://google.com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid protocol name")
	{
		std::string input = "htp://google.com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string does not conatin a hostname")
	{
		std::string input = "http://";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string does not conatin a domen")
	{
		std::string input = "http://google";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid character in hostname")
	{
		std::string input = "http://goo#gle";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://.google.com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google.com.";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google-.com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google.-com";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid port")
	{
		std::string input = "http://google.com:0";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}

	WHEN("input string conatin invalid port")
	{
		std::string input = "http://google.com:65536";
		THEN("error is expected")
		{
			CHECK_THROWS_AS(ParseUrl(input), std::runtime_error);
		}
	}
}

SCENARIO("Parse valid url")
{
	WHEN("input string contain only protocol and host")
	{
		std::string input = "http://example.com";
		THEN("result url must contain default port and same host and document")
		{
			Url url = ParseUrl(input);
			CHECK(url.port == "80");
			CHECK(url.host == "example.com");
			CHECK(url.document == "");
		}
	}

	WHEN("input string contain only protocol in different case and host")
	{
		std::string input = "htTp://example.com";
		THEN("result url must contain default port and same host and document")
		{
			Url url = ParseUrl(input);
			CHECK(url.port == "80");
			CHECK(url.host == "example.com");
			CHECK(url.document == "");
		}
	}

	WHEN("input string contain protocol equal 1")
	{
		std::string input = "http://example.com:8080/index.html";
		THEN("result url must contain same port, host and document")
		{
			Url url = ParseUrl(input);
			CHECK(url.port == "8080");
			CHECK(url.host == "example.com");
			CHECK(url.document == "index.html");
		}
	}

	WHEN("input string contain protocol equal 65535")
	{
		std::string input = "http://example.com:65535/index.html";
		THEN("result url must contain same port, host and document")
		{
			Url url = ParseUrl(input);
			CHECK(url.port == "65535");
			CHECK(url.host == "example.com");
			CHECK(url.document == "index.html");
		}
	}

	WHEN("input string contain only protocol and host")
	{
		std::string input = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		THEN("result url must contain default port and same host and document")
		{
			Url url = ParseUrl(input);
			CHECK(url.port == "80");
			CHECK(url.host == "www.mysite.com");
			CHECK(url.document == "docs/document1.html?page=30&lang=en#title");
		}
	}
}