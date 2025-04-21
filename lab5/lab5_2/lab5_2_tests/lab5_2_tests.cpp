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

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
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

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
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

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
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

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
		}
	}

	WHEN("create string with string and length in parameters")
	{
		CMyString str("hello", 2);
		THEN("string should contain he")
		{
			CHECK(str.GetCapacity() == 2);
			CHECK(str.GetLength() == 2);
			CHECK(std::string(str.GetStringData()) == "he");
		}

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
		}
	}

	WHEN("create string with string and length in parameters")
	{
		CMyString str("hello", 10);
		THEN("string should contain hello")
		{
			CHECK(str.GetCapacity() == 10);
			CHECK(str.GetLength() == 10);
			CHECK(std::string(str.GetStringData()) == "hello");
		}

		AND_WHEN("clear string")
		{
			str.Clear();
			THEN("string should be an empty")
			{
				CHECK(str.GetCapacity() == 0);
				CHECK(str.GetLength() == 0);
				CHECK(std::string(str.GetStringData()) == "");
			}
		}
	}
}

SCENARIO("test construct with std::string")
{
	WHEN("construct with empty std::string")
	{
		std::string empty;
		CMyString str(empty);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == empty);
		}
	}

	WHEN("construct with std::string contains one char")
	{
		std::string copiedStr("a");
		CMyString str(copiedStr);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == copiedStr);
		}
	}

	WHEN("construct with std::string contains string hello")
	{
		std::string copiedStr("hello");
		CMyString str(copiedStr);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == copiedStr);
		}
	}
}

SCENARIO("test copying constructor")
{
	WHEN("construct with empty CMyString")
	{
		CMyString empty;
		CMyString str(empty);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
		}
	}

	WHEN("construct with CMyString contains one char")
	{
		CMyString copiedStr("a");
		CMyString str(copiedStr);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == "a");
		}
	}

	WHEN("construct with CMyString contains string hello")
	{
		CMyString copiedStr("hello");
		CMyString str(copiedStr);
		THEN("string should be an equal")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
		}
	}
}

SCENARIO("test move constructor")
{
	WHEN("construct with empty CMyString")
	{
		CMyString empty;
		CMyString str(std::move(empty));
		THEN("string should be an equal source string and empty string should remain empty")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
			CHECK(empty.GetCapacity() == 0);
			CHECK(empty.GetLength() == 0);
			CHECK(std::string(empty.GetStringData()) == "");
		}
	}

	WHEN("construct with CMyString contains one char")
	{
		CMyString copiedStr("a");
		CMyString str(std::move(copiedStr));
		THEN("string should be an equal source string and copeidStr should be an empty")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == "a");
			CHECK(copiedStr.GetCapacity() == 0);
			CHECK(copiedStr.GetLength() == 0);
			CHECK(std::string(copiedStr.GetStringData()) == "");
		}
	}

	WHEN("construct with CMyString contains string hello")
	{
		CMyString copiedStr("hello");
		CMyString str(std::move(copiedStr));
		THEN("string should be an equal source string and copeidStr should be an empty")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
			CHECK(copiedStr.GetCapacity() == 0);
			CHECK(copiedStr.GetLength() == 0);
			CHECK(std::string(copiedStr.GetStringData()) == "");
		}
	}
}

SCENARIO("test move operator")
{
	WHEN("move empty CMyString")
	{
		CMyString empty;
		CMyString str("content");
		str = std::move(empty);
		THEN("strings should exchange contents")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
			CHECK(empty.GetCapacity() == 0);
			CHECK(empty.GetLength() == 0);
			CHECK(std::string(empty.GetStringData()) == "");
		}
	}

	WHEN("move CMyString contains one char")
	{
		CMyString copiedStr("a");
		CMyString str("content");
		str = std::move(copiedStr);
		THEN("strings should exchange contents")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == "a");
			CHECK(copiedStr.GetCapacity() == 0);
			CHECK(copiedStr.GetLength() == 0);
			CHECK(std::string(copiedStr.GetStringData()) == "");
		}
	}

	WHEN("move CMyString contains string hello")
	{
		CMyString copiedStr("hello");
		CMyString str("content");
		str = std::move(copiedStr);
		THEN("strings should exchange contents")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
			CHECK(copiedStr.GetCapacity() == 0);
			CHECK(copiedStr.GetLength() == 0);
			CHECK(std::string(copiedStr.GetStringData()) == "");
		}
	}

	WHEN("move self to self")
	{
		CMyString str("hello");
		str = std::move(str);
		THEN("strings should unchanged")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
		}
	}
}

SCENARIO("assignment operator testing")
{
	WHEN("assign a string to itself")
	{
		CMyString str("content");
		str = str;
		THEN("string should not change")
		{
			CHECK(str.GetCapacity() == 7);
			CHECK(str.GetLength() == 7);
			CHECK(std::string(str.GetStringData()) == "content");
		}
	}

	WHEN("assign empty CMyString")
	{
		CMyString empty;
		CMyString str("content");
		str = empty;
		THEN("string must be assigned the value of another string and the capacity should not change")
		{
			CHECK(str.GetCapacity() == 0);
			CHECK(str.GetLength() == 0);
			CHECK(std::string(str.GetStringData()) == "");
		}
	}

	WHEN("construct with CMyString contains one char")
	{
		CMyString copiedStr("a");
		CMyString str("content");
		str = copiedStr;
		THEN("string must be assigned the value of another string and the capacity should not change")
		{
			CHECK(str.GetCapacity() == 1);
			CHECK(str.GetLength() == 1);
			CHECK(std::string(str.GetStringData()) == "a");
		}
	}

	WHEN("construct with CMyString contains string hello")
	{
		CMyString copiedStr("hello");
		CMyString str("content");
		str = copiedStr;
		THEN("string must be assigned the value of another string and the capacity should not change")
		{
			CHECK(str.GetCapacity() == 5);
			CHECK(str.GetLength() == 5);
			CHECK(std::string(str.GetStringData()) == "hello");
		}
	}

	WHEN("construct with CMyString contains string hello world")
	{
		CMyString copiedStr("hello world");
		CMyString str("content");
		str = copiedStr;
		THEN("string must be assigned the value of another string and the capacity should change")
		{
			CHECK(str.GetCapacity() == 11);
			CHECK(str.GetLength() == 11);
			CHECK(std::string(str.GetStringData()) == "hello world");
		}
	}
}

SCENARIO("test substring")
{
	GIVEN("empty CMyString")
	{
		CMyString str;

		WHEN("substring with start = 0 and length = 0 params")
		{
			CMyString subStr = str.SubString(0, 0);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}

		WHEN("substring with start = 1 and length = 0 params")
		{
			CMyString subStr = str.SubString(1, 0);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}

		WHEN("substring with start = 0 and length = 1 params")
		{
			CMyString subStr = str.SubString(0, 1);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}

		WHEN("substring with start = 1 and length = 1 params")
		{
			CMyString subStr = str.SubString(1, 1);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}
	}

	GIVEN("CMyString contains word content")
	{
		CMyString str("content");

		WHEN("substring with start = 0 and length = 0 params")
		{
			CMyString subStr = str.SubString(0, 0);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}

		WHEN("substring with start = 1 and length = 0 params")
		{
			CMyString subStr = str.SubString(1, 0);
			THEN("subStr should be an empty")
			{
				CHECK(subStr.GetCapacity() == 0);
				CHECK(subStr.GetLength() == 0);
				CHECK(std::string(subStr.GetStringData()) == "");
			}
		}

		WHEN("substring with start = 0 and length = 1 params")
		{
			CMyString subStr = str.SubString(0, 1);
			THEN("subStr should contain c")
			{
				CHECK(subStr.GetCapacity() == 1);
				CHECK(subStr.GetLength() == 1);
				CHECK(std::string(subStr.GetStringData()) == "c");
			}
		}

		WHEN("substring with start = 1 and length = 1 params")
		{
			CMyString subStr = str.SubString(1, 1);
			THEN("subStr should contain o")
			{
				CHECK(subStr.GetCapacity() == 1);
				CHECK(subStr.GetLength() == 1);
				CHECK(std::string(subStr.GetStringData()) == "o");
			}
		}

		WHEN("substring with start = 0 and length = 6 params")
		{
			CMyString subStr = str.SubString(0, 6);
			THEN("subStr should contain conten")
			{
				CHECK(subStr.GetCapacity() == 6);
				CHECK(subStr.GetLength() == 6);
				CHECK(std::string(subStr.GetStringData()) == "conten");
			}
		}

		WHEN("substring with start = 0 and length = 7 params")
		{
			CMyString subStr = str.SubString(0, 7);
			THEN("subStr should contain content")
			{
				CHECK(subStr.GetCapacity() == 7);
				CHECK(subStr.GetLength() == 7);
				CHECK(std::string(subStr.GetStringData()) == "content");
			}
		}

		WHEN("substring with start = 0 and length = 8 params")
		{
			CMyString subStr = str.SubString(0, 8);
			THEN("subStr should contain content")
			{
				CHECK(subStr.GetCapacity() == 7);
				CHECK(subStr.GetLength() == 7);
				CHECK(std::string(subStr.GetStringData()) == "content");
			}
		}

		WHEN("substring with start = 6 and length = 1 params")
		{
			CMyString subStr = str.SubString(6, 1);
			THEN("subStr should contain t")
			{
				CHECK(subStr.GetCapacity() == 1);
				CHECK(subStr.GetLength() == 1);
				CHECK(std::string(subStr.GetStringData()) == "t");
			}
		}

		WHEN("substring with start = 3 and length = 3 params")
		{
			CMyString subStr = str.SubString(3, 3);
			THEN("subStr should contain ten")
			{
				CHECK(subStr.GetCapacity() == 3);
				CHECK(subStr.GetLength() == 3);
				CHECK(std::string(subStr.GetStringData()) == "ten");
			}
		}
	}
}

SCENARIO("test addition operator")
{
	WHEN("add two empty strings")
	{
		CMyString str1;
		CMyString str2;
		CMyString res = str1 + str2;
		THEN("result string should be empty two")
		{
			CHECK(res.GetCapacity() == 0);
			CHECK(res.GetLength() == 0);
			CHECK(std::string(res.GetStringData()) == "");
		}
	}

	WHEN("add empty string with non-empty")
	{
		CMyString str1;
		CMyString str2("word");
		CMyString res = str1 + str2;
		THEN("result string should contain second string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("add non-empty string with empty")
	{
		CMyString str1("word");
		CMyString str2;
		CMyString res = str1 + str2;
		THEN("result string should contain first string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("addition non-empty strings")
	{
		CMyString str1("word");
		CMyString str2(" hello");
		CMyString res = str1 + str2;
		THEN("result string should contain both strings and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 20);
			CHECK(res.GetLength() == 10);
			CHECK(std::string(res.GetStringData()) == "word hello");
		}
	}
}

SCENARIO("test addition with assigment operator")
{
	WHEN("add two empty strings")
	{
		CMyString str1;
		CMyString str2;
		str1 += str2;
		THEN("result string should be empty two")
		{
			CHECK(str1.GetCapacity() == 0);
			CHECK(str1.GetLength() == 0);
			CHECK(std::string(str1.GetStringData()) == "");
		}
	}

	WHEN("add empty string with non-empty")
	{
		CMyString str1;
		CMyString str2("word");
		str1 += str2;
		THEN("result string should contain second string and its capacity should be doubled")
		{
			CHECK(str1.GetCapacity() == 8);
			CHECK(str1.GetLength() == 4);
			CHECK(std::string(str1.GetStringData()) == "word");
		}
	}

	WHEN("add non-empty string with empty")
	{
		CMyString str1("word");
		CMyString str2;
		str1 += str2;
		THEN("result string should contain first string and its capacity should be doubled")
		{
			CHECK(str1.GetCapacity() == 8);
			CHECK(str1.GetLength() == 4);
			CHECK(std::string(str1.GetStringData()) == "word");
		}
	}

	WHEN("addition non-empty strings")
	{
		CMyString str1("word");
		CMyString str2(" hello");
		str1 += str2;
		THEN("result string should contain both strings and its capacity should be doubled")
		{
			CHECK(str1.GetCapacity() == 20);
			CHECK(str1.GetLength() == 10);
			CHECK(std::string(str1.GetStringData()) == "word hello");
		}
	}
}

SCENARIO("test addition CMyString with std::string operator")
{
	WHEN("add two empty strings")
	{
		CMyString str1;
		std::string str2;
		CMyString res = str1 + str2;
		THEN("result string should be empty two")
		{
			CHECK(res.GetCapacity() == 0);
			CHECK(res.GetLength() == 0);
			CHECK(std::string(res.GetStringData()) == "");
		}
	}

	WHEN("add empty string with non-empty")
	{
		CMyString str1;
		std::string str2("word");
		CMyString res = str1 + str2;
		THEN("result string should contain second string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("add non-empty string with empty")
	{
		CMyString str1("word");
		std::string str2;
		CMyString res = str1 + str2;
		THEN("result string should contain first string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("addition non-empty strings")
	{
		CMyString str1("word");
		std::string str2(" hello");
		CMyString res = str1 + str2;
		THEN("result string should contain both strings and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 20);
			CHECK(res.GetLength() == 10);
			CHECK(std::string(res.GetStringData()) == "word hello");
		}
	}
}

SCENARIO("test addition CMyString with pString operator")
{
	WHEN("add two empty strings")
	{
		CMyString str1;
		const char* str2 = "";
		CMyString res = str1 + str2;
		THEN("result string should be empty two")
		{
			CHECK(res.GetCapacity() == 0);
			CHECK(res.GetLength() == 0);
			CHECK(std::string(res.GetStringData()) == "");
		}
	}

	WHEN("add empty string with non-empty")
	{
		CMyString str1;
		const char* str2 = "word";
		CMyString res = str1 + str2;
		THEN("result string should contain second string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("add non-empty string with empty")
	{
		CMyString str1("word");
		const char* str2 = "";
		CMyString res = str1 + str2;
		THEN("result string should contain first string and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 8);
			CHECK(res.GetLength() == 4);
			CHECK(std::string(res.GetStringData()) == "word");
		}
	}

	WHEN("addition non-empty strings")
	{
		CMyString str1("word");
		const char* str2 = " hello";
		CMyString res = str1 + str2;
		THEN("result string should contain both strings and its capacity should be doubled")
		{
			CHECK(res.GetCapacity() == 20);
			CHECK(res.GetLength() == 10);
			CHECK(std::string(res.GetStringData()) == "word hello");
		}
	}
}

SCENARIO("testing comparison")
{
	WHEN("both strings are empty")
	{
		CMyString str1;
		CMyString str2;
		CHECK(str1 == str2);
		CHECK(!(str1 != str2));
		CHECK(!(str1 > str2));
		CHECK(!(str1 < str2));
		CHECK(str1 >= str2);
		CHECK(str1 <= str2);
	}

	WHEN("first string is empty and the second is not empty")
	{
		CMyString str1;
		CMyString str2("abc");
		CHECK(!(str1 == str2));
		CHECK(str1 != str2);
		CHECK(!(str1 > str2));
		CHECK(str1 < str2);
		CHECK(!(str1 >= str2));
		CHECK(str1 <= str2);
	}

	WHEN("first string is not empty and the second is empty")
	{
		CMyString str1("abc");
		CMyString str2;
		CHECK(!(str1 == str2));
		CHECK(str1 != str2);
		CHECK(str1 > str2);
		CHECK(!(str1 < str2));
		CHECK(str1 >= str2);
		CHECK(!(str1 <= str2));
	}

	WHEN("first string is less than the second in alphabetical order")
	{
		CMyString str1("abc");
		CMyString str2("def");
		CHECK(!(str1 == str2));
		CHECK(str1 != str2);
		CHECK(!(str1 > str2));
		CHECK(str1 < str2);
		CHECK(!(str1 >= str2));
		CHECK(str1 <= str2);
	}

	WHEN("first string is shorter than the second line")
	{
		CMyString str1("abc");
		CMyString str2("abcd");
		CHECK(!(str1 == str2));
		CHECK(str1 != str2);
		CHECK(!(str1 > str2));
		CHECK(str1 < str2);
		CHECK(!(str1 >= str2));
		CHECK(str1 <= str2);
	}

	WHEN("lines are the equal")
	{
		CMyString str1("abc");
		CMyString str2("abc");
		CHECK(str1 == str2);
		CHECK(!(str1 != str2));
		CHECK(!(str1 > str2));
		CHECK(!(str1 < str2));
		CHECK(str1 >= str2);
		CHECK(str1 <= str2);
	}
}

SCENARIO("indexed access")
{
	GIVEN("string contains Hello")
	{
		CMyString str("Hello");

		WHEN("read by indexex")
		{
			THEN("must get the correct symbols")
			{
				CHECK(str[0] == 'H');
				CHECK(str[1] == 'e');
				CHECK(str[2] == 'l');
				CHECK(str[3] == 'l');
				CHECK(str[4] == 'o');
			}
		}

		WHEN("write by indexes")
		{
			str[0] = 'W';
			str[1] = 'o';
			str[2] = 'r';
			str[3] = 'l';
			str[4] = 'd';
			THEN("string should change")
			{
				CHECK(std::string(str.GetStringData()) == "World");
			}
		}
	}
}

SCENARIO("string output test")
{
	std::ostringstream output;

	GIVEN("empty string")
	{
		CMyString str;
		WHEN("output a string to the output stream")
		{
			output << str;
			THEN("output stream should not contain anything")
			{
				CHECK(std::string(str.GetStringData()) == "");
			}
		}
	}

	GIVEN("string with 1 char")
	{
		CMyString str("a");
		WHEN("output a string to the output stream")
		{
			output << str;
			THEN("output stream should contain a")
			{
				CHECK(std::string(str.GetStringData()) == "a");
			}
		}
	}

	GIVEN("string contains Hello world")
	{
		CMyString str("Hello world");
		WHEN("output a string to the output stream")
		{
			output << str;
			THEN("output stream should contain Hello world")
			{
				CHECK(std::string(str.GetStringData()) == "Hello world");
			}
		}
	}
}

SCENARIO("string input test")
{
	GIVEN("empty input stream")
	{
		std::istringstream input("");
		WHEN("read string from stream")
		{
			CMyString str;
			input >> str;
			THEN("string should be an empty")
			{
				CHECK(std::string(str.GetStringData()) == "");
			}
		}
	}

	GIVEN("input stream contains one char")
	{
		std::istringstream input("a");
		WHEN("read string from stream")
		{
			CMyString str;
			input >> str;
			THEN("string must contain char a")
			{
				CHECK(std::string(str.GetStringData()) == "a");
			}
		}
	}

	GIVEN("input stream contains hello")
	{
		std::istringstream input("hello");
		WHEN("read string from stream")
		{
			CMyString str;
			input >> str;
			THEN("string must contain hello")
			{
				CHECK(std::string(str.GetStringData()) == "hello");
			}
		}
	}
}

SCENARIO("iterators test")
{
	std::ostringstream output;

	GIVEN("string contains 'h' char")
	{
		CMyString str("h");
		WHEN("get iterator begin")
		{
			auto it = str.begin();
			THEN("begin iterator must have a valid value")
			{
				CHECK(*it == 'h');
			}
		}
	}

	GIVEN("string contains 'hello'")
	{
		CMyString str("hello");
		WHEN("prefix increment and dereference iterators one by one")
		{
			auto it = str.begin();
			THEN("iterators must have a valid value")
			{
				CHECK(*it++ == 'h');
				CHECK(*it++ == 'e');
				CHECK(*it++ == 'l');
				CHECK(*it++ == 'l');
				CHECK(*it == 'o');

				AND_WHEN("prefix decrement and dereference iterators one by one")
				{
					CHECK(*it-- == 'o');
					CHECK(*it-- == 'l');
					CHECK(*it-- == 'l');
					CHECK(*it-- == 'e');
					CHECK(*it == 'h');
				}
			}
		}

		WHEN("postfix increment and dereference iterators one by one")
		{
			auto it = str.begin();
			THEN("iterators must have a valid value")
			{
				CHECK(*++it == 'e');
				CHECK(*++it == 'l');
				CHECK(*++it == 'l');
				CHECK(*++it == 'o');

				AND_WHEN("postfix increment and dereference one by one")
				{
					CHECK(*--it == 'l');
					CHECK(*--it == 'l');
					CHECK(*--it == 'e');
					CHECK(*--it == 'h');
				}
			}
		}

		WHEN("output in for range cycle")
		{
			for (auto it = str.begin(); it != str.end(); ++it)
			{
				output << *it;
			}
			THEN("output stream must be equal to the string")
			{
				CHECK(std::string(str.GetStringData()) == output.str());
			}
		}

		WHEN("output in temporary range cycle")
		{
			for (auto s : str)
			{
				output << s;
			}
			THEN("output stream must be equal to the string")
			{
				CHECK(std::string(str.GetStringData()) == output.str());
			}
		}

		WHEN("add a first index to the iterator")
		{
			auto it = str.begin();
			it = it + 1;
			THEN("iterator must have a shifted value")
			{
				CHECK(*it == 'e');
			}
		}

		WHEN("add a last index to the iterator")
		{
			auto it = str.begin();
			it = it + 4;
			THEN("iterator must have a shifted value")
			{
				CHECK(*it == 'o');
			}
		}

		WHEN("add with assignment a first index to the iterator")
		{
			auto it = str.begin();
			it += 1;
			THEN("iterator must have a shifted value")
			{
				CHECK(*it == 'e');
			}
		}

		WHEN("add with assignment a last index to the iterator")
		{
			auto it = str.begin();
			it += 4;
			THEN("iterator must have a shifted value")
			{
				CHECK(*it == 'o');
			}
		}

		WHEN("check two identical iterators for equality")
		{
			auto it1 = str.begin();
			auto it2 = str.begin();
			THEN("comparison should return true")
			{
				CHECK(it1 == it2);
				CHECK(!(it1 != it2));
			}
		}

		WHEN("check two different iterators for equality")
		{
			auto it1 = str.begin();
			auto it2 = it1 + 1;
			THEN("comparison should return false")
			{
				CHECK(!(it1 == it2));
				CHECK(it1 != it2);
			}
		}

		WHEN("subtract from the second iterator which is greater than the first by 3")
		{
			auto it1 = str.begin();
			auto it2 = it1 + 3;
			THEN("the difference should be 3")
			{
				CHECK(it2 - it1 == 3);
			}
		}

		WHEN("subtract from the first iterator which is less than the first by 3")
		{
			auto it1 = str.begin();
			auto it2 = it1 + 3;
			THEN("the difference should be -3")
			{
				CHECK(it1 - it2 == -3);
			}
		}

		WHEN("read the iterator by index")
		{
			auto it = str.begin();
			THEN("iterator must have a correct value")
			{
				CHECK(it[0] == 'h');
				CHECK(it[1] == 'e');
				CHECK(it[2] == 'l');
				CHECK(it[3] == 'l');
				CHECK(it[4] == 'o');
			}
		}

		WHEN("write the iterator by index")
		{
			auto it = str.begin();
			it[0] = 'w';
			it[1] = 'o';
			it[2] = 'r';
			it[3] = 'l';
			it[4] = 'd';

			THEN("iterator must have a correct value")
			{
				CHECK(it[0] == 'w');
				CHECK(it[1] == 'o');
				CHECK(it[2] == 'r');
				CHECK(it[3] == 'l');
				CHECK(it[4] == 'd');
			}
		}
	}
}

SCENARIO("test reverse iterators")
{
	std::ostringstream output;

	GIVEN("string contains 'hello'")
	{
		CMyString str("hello");
		WHEN("output in for range cycle")
		{
			for (auto it = str.rbegin(); it != str.rend(); ++it)
			{
				output << *it;
			}
			THEN("output stream must be equal to the reverse string")
			{
				CHECK("olleh" == output.str());
			}
		}

		WHEN("prefix increment and dereference iterators one by one")
		{
			auto it = str.begin();
			THEN("iterators must have a valid value")
			{
				CHECK(*it++ == 'h');
				CHECK(*it++ == 'e');
				CHECK(*it++ == 'l');
				CHECK(*it++ == 'l');
				CHECK(*it == 'o');

				AND_WHEN("prefix decrement and dereference iterators one by one")
				{
					CHECK(*it-- == 'o');
					CHECK(*it-- == 'l');
					CHECK(*it-- == 'l');
					CHECK(*it-- == 'e');
					CHECK(*it == 'h');
				}
			}
		}

		WHEN("postfix increment and dereference iterators one by one")
		{
			auto it = str.rbegin();
			THEN("iterators must have a valid value")
			{
				CHECK(*++it == 'l');
				CHECK(*++it == 'l');
				CHECK(*++it == 'e');
				CHECK(*++it == 'h');

				AND_WHEN("postfix increment and dereference one by one")
				{
					CHECK(*--it == 'e');
					CHECK(*--it == 'l');
					CHECK(*--it == 'l');
					CHECK(*--it == 'o');
				}
			}
		}
	}
}