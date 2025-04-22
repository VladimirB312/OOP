#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CHttpUrl.h"
#include "../CUrlParsingError.h"

SCENARIO("create url from invalid string")
{
	WHEN("input string is empty")
	{
		std::string input;
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string does not conatin a protocol")
	{
		std::string input = "google.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string does not conatin a protocol name")
	{
		std::string input = "://google.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid protocol name")
	{
		std::string input = "htp://google.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid protocol name")
	{
		std::string input = "htp://google.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string does not conatin a hostname")
	{
		std::string input = "http://";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string does not conatin a domen")
	{
		std::string input = "http://google";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid character in hostname")
	{
		std::string input = "http://goo#gle";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://.google.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google.com.";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google-.com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid hostname structure")
	{
		std::string input = "http://google.-com";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid port")
	{
		std::string input = "http://google.com:0";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}

	WHEN("input string conatin invalid port")
	{
		std::string input = "http://google.com:65536";
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(input), CUrlParsingError);
		}
	}
}

SCENARIO("create url from valid string")
{
	WHEN("input string contain only protocol and host")
	{
		std::string input = "http://example.com";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetURL() == "http://example.com/");
		}
	}

	WHEN("input string contain protocol and host and port by default")
	{
		std::string input = "http://example.com:80";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "http://example.com/");
		}
	}

	WHEN("input string contain only protocol and host")
	{
		std::string input = "https://example.com";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "https://example.com/");
		}
	}

	WHEN("input string contain protocol and host and port by default")
	{
		std::string input = "https://example.com:443";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "https://example.com/");
		}
	}

	WHEN("input string contain only protocol in different case and host")
	{
		std::string input = "htTp://example.com";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "http://example.com/");
		}
	}

	WHEN("input string contain port equal 1")
	{
		std::string input = "http://example.com:1/index.html";
		THEN("result url must contain same port, host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 1);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/index.html");
			CHECK(url.GetURL() == "http://example.com:1/index.html");
		}
	}

	WHEN("input string contain port equal 65535")
	{
		std::string input = "http://example.com:65535/index.html";
		THEN("result url must contain same port, host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 65535);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/index.html");
			CHECK(url.GetURL() == "http://example.com:65535/index.html");
		}
	}

	WHEN("input string contain port not equal default protocol's port")
	{
		std::string input = "https://example.com:8080/index.html";
		THEN("result url must contain same port, host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 8080);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/index.html");
			CHECK(url.GetURL() == "https://example.com:8080/index.html");
		}
	}

	WHEN("input string contain port not equal default protocol's port")
	{
		std::string input = "http://example.com:8080/index.html";
		THEN("result url must contain same port, host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 8080);
			CHECK(url.GetDomain() == "example.com");
			CHECK(url.GetDocument() == "/index.html");
			CHECK(url.GetURL() == "http://example.com:8080/index.html");
		}
	}

	WHEN("input string contain only protocol and host")
	{
		std::string input = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		THEN("result url must contain default port and same host and document")
		{
			CHttpUrl url(input);
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
			CHECK(url.GetURL() == input);
		}
	}
}

SCENARIO("create url from args list")
{
	WHEN("protocol is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("google.com", "", static_cast<Protocol>(2), 443), CUrlParsingError);
		}
	}

	WHEN("protocol is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("google.com", "", static_cast<Protocol>(-1), 443), CUrlParsingError);
		}
	}

	WHEN("domain is empty")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("goo$gle.com", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl(".google.com", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("google", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("google-.com", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CHttpUrl("google.-com", "", Protocol::HTTP, 443), CUrlParsingError);
		}
	}

	WHEN("arguments do not have a port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTP);
		THEN("the port should be set by default")
		{
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "http://google.com/");
		}
	}

	WHEN("arguments do not have a port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTPS);
		THEN("the port should be set by default")
		{
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "https://google.com/");
		}
	}

	WHEN("arguments have a port that matches the default port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTP, 80);
		THEN("the port should be set by default")
		{
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "http://google.com/");
		}
	}

	WHEN("arguments have a port that matches the default port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTPS, 443);
		THEN("the port should be set by default")
		{
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "https://google.com/");
		}
	}

	WHEN("arguments have a port that does not match the default port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTP, 112);
		THEN("the port should be in get url")
		{
			CHECK(url.GetPort() == 112);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "http://google.com:112/");
		}
	}

	WHEN("arguments have a port that does not match the default port")
	{
		CHttpUrl url("google.com", "", Protocol::HTTPS, 324);
		THEN("the port should be in get url")
		{
			CHECK(url.GetPort() == 324);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/");
			CHECK(url.GetURL() == "https://google.com:324/");
		}
	}

	WHEN("arguments contain document without slash")
	{
		CHttpUrl url("google.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTPS);
		THEN("url should contain document with slash")
		{
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
			CHECK(url.GetURL() == "https://google.com/docs/document1.html?page=30&lang=en#title");
		}
	}

	WHEN("arguments contain document with slash")
	{
		CHttpUrl url("google.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTPS);
		THEN("url should contain document with slash")
		{
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDomain() == "google.com");
			CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
			CHECK(url.GetURL() == "https://google.com/docs/document1.html?page=30&lang=en#title");
		}
	}
}