#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CStringList.h"

SCENARIO("empty and size testing")
{
	WHEN("create cstringlist")
	{
		CStringList l;
		THEN("list should be empty size 0")
		{
			CHECK(l.IsEmpty());
			CHECK(l.GetSize() == 0);
		}

		AND_WHEN("clear list")
		{
			l.Clear();
			THEN("list will not change")
			{
				CHECK(l.IsEmpty());
				CHECK(l.GetSize() == 0);
			}

			AND_WHEN("push back 1 element")
			{
				l.PushBack("one");
				THEN("list should not be empty, size 1")
				{
					CHECK(!l.IsEmpty());
					CHECK(l.GetSize() == 1);
				}
			}
		}

		AND_WHEN("push back 1 element")
		{
			l.PushBack("one");
			THEN("list should not be empty, size 1")
			{
				CHECK(!l.IsEmpty());
				CHECK(l.GetSize() == 1);
			}

			AND_WHEN("push back another element")
			{
				l.PushBack("two");
				THEN("list should not be empty, size 2")
				{
					CHECK(!l.IsEmpty());
					CHECK(l.GetSize() == 2);
				}

				AND_WHEN("clear list")
				{
					l.Clear();
					THEN("list should be empty, size 0")
					{
						CHECK(l.IsEmpty());
						CHECK(l.GetSize() == 0);
					}

					AND_WHEN("push back 1 element")
					{
						l.PushBack("one");
						THEN("list should not be empty, size 1")
						{
							CHECK(!l.IsEmpty());
							CHECK(l.GetSize() == 1);
						}
					}
				}
			}
		}
		AND_WHEN("push front 1 element")
		{
			l.PushFront("one");
			THEN("list should not be empty, size 1")
			{
				CHECK(!l.IsEmpty());
				CHECK(l.GetSize() == 1);
			}

			AND_WHEN("push front another element")
			{
				l.PushFront("two");
				THEN("list should not be empty, size 2")
				{
					CHECK(!l.IsEmpty());
					CHECK(l.GetSize() == 2);
				}

				AND_WHEN("clear list")
				{
					l.Clear();
					THEN("list should be empty, size 0")
					{
						CHECK(l.IsEmpty());
						CHECK(l.GetSize() == 0);
					}

					AND_WHEN("push front 1 element")
					{
						l.PushFront("one");
						THEN("list should not be empty, size 1")
						{
							CHECK(!l.IsEmpty());
							CHECK(l.GetSize() == 1);
						}
					}
				}
			}
		}
	}
}

SCENARIO("iterators testing")
{
	WHEN("list is empty")
	{
		CStringList l;
		auto itBegin = l.begin();
		auto itEnd = l.end();
		THEN("begin and end iterators are equal")
		{
			CHECK(itBegin == itEnd);
		}
		AND_WHEN("try to dereference iterators")
		{
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(*itBegin, std::logic_error);
				CHECK_THROWS_AS(*itEnd, std::logic_error);
			}
		}
	}

	GIVEN("CStringList with four elements")
	{
		CStringList l;
		l.PushBack("one");
		l.PushBack("two");
		l.PushBack("three");
		l.PushBack("four");

		WHEN("get begin iterator")
		{
			auto it = l.begin();
			THEN("dereferenced iterator must be equal to the first element")
			{
				CHECK(*it == "one");
			}

			AND_WHEN("decrement iterator and try to dereference")
			{
				--it;
				THEN("an exception should be thrown")
				{
					CHECK_THROWS_AS(*it, std::logic_error);
				}
			}

			AND_WHEN("prefix increment iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*++it == "two");
					CHECK(*++it == "three");
					CHECK(*++it == "four");

					AND_WHEN("prefix decrement iterator")
					{
						THEN("each reduction must be equal to each element")
						{
							CHECK(*--it == "three");
							CHECK(*--it == "two");
							CHECK(*--it == "one");
						}
					}
				}
			}

			AND_WHEN("postfix increment iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*it++ == "one");
					CHECK(*it++ == "two");
					CHECK(*it++ == "three");
					CHECK(*it++ == "four");

					AND_WHEN("postfix decrement iterator")
					{
						it--;
						THEN("each reduction must be equal to each element")
						{
							CHECK(*it-- == "four");
							CHECK(*it-- == "three");
							CHECK(*it-- == "two");
							CHECK(*it-- == "one");
						}
					}
				}
			}
		}

		WHEN("get end iterator and try to dereference")
		{
			auto it = l.end();
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(*it, std::logic_error);
			}
		}

		WHEN("get end iterator and decrement it")
		{
			auto it = l.end();
			--it;
			THEN("dereferenced iterator must be equal to the last element")
			{
				CHECK(*it == "four");
			}

			AND_WHEN("prefix decrement iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*--it == "three");
					CHECK(*--it == "two");
					CHECK(*--it == "one");
				}
			}
		}
	}
}

SCENARIO("reverse iterators testing")
{
	GIVEN("CStringList with four elements")
	{
		CStringList l;
		l.PushBack("one");
		l.PushBack("two");
		l.PushBack("three");
		l.PushBack("four");

		WHEN("get rbegin iterator")
		{
			auto it = l.rbegin();
			THEN("dereferenced iterator must be equal to the last element")
			{
				CHECK(*it == "four");
			}

			AND_WHEN("decrement iterator and try to dereference")
			{
				--it;
				THEN("an exception should be thrown")
				{
					CHECK_THROWS_AS(*it, std::logic_error);
				}
			}

			AND_WHEN("prefix increment reverse iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*++it == "three");
					CHECK(*++it == "two");
					CHECK(*++it == "one");

					AND_WHEN("prefix decrement iterator")
					{
						THEN("each reduction must be equal to each element")
						{
							CHECK(*--it == "two");
							CHECK(*--it == "three");
							CHECK(*--it == "four");
						}
					}
				}
			}

			AND_WHEN("postfix increment reverse iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*it++ == "four");
					CHECK(*it++ == "three");
					CHECK(*it++ == "two");
					CHECK(*it++ == "one");

					AND_WHEN("postfix decrement iterator")
					{
						it--;
						THEN("each reduction must be equal to each element")
						{
							CHECK(*it-- == "one");
							CHECK(*it-- == "two");
							CHECK(*it-- == "three");
							CHECK(*it-- == "four");
						}
					}
				}
			}
		}

		WHEN("get rend iterator and try to dereference")
		{
			auto it = l.rend();
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(*it, std::logic_error);
			}
		}

		WHEN("get rend iterator and decrement it")
		{
			auto it = l.rend();
			--it;
			THEN("dereferenced reverse iterator must be equal to the first element")
			{
				CHECK(*it == "one");
			}

			AND_WHEN("prefix decrement iterator")
			{
				THEN("each addition must be equal to each element")
				{
					CHECK(*--it == "two");
					CHECK(*--it == "three");
					CHECK(*--it == "four");
				}
			}
		}
	}
}

SCENARIO("range for cycle testing")
{
	std::ostringstream output;

	GIVEN("empty list")
	{
		CStringList l;

		WHEN("go through all the elements in the range for loop")
		{
			THEN("it will never enter the cycle")
			{
				int i = 0;
				for (auto it = l.begin(); it != l.end(); ++it)
				{
					++i;
				}
				CHECK(i == 0);
			}
		}

		WHEN("go through all the elements in the temporary range loop")
		{
			THEN("it will never enter the cycle")
			{
				int i = 0;
				for (auto s : l)
				{
					++i;
				}
				CHECK(i == 0);
			}
		}
	}

	GIVEN("list with four elements")
	{
		CStringList l;
		l.PushBack("one");
		l.PushBack("two");
		l.PushBack("three");
		l.PushBack("four");

		WHEN("go through all the elements in the range for loop")
		{
			THEN("output should be contain all elements")
			{
				for (auto it = l.begin(); it != l.end(); ++it)
				{
					output << *it;
				}
				CHECK(output.str() == "onetwothreefour");
			}
		}

		WHEN("go through all the elements in the reverse range for loop")
		{
			THEN("output should be contain all elements in reversed order")
			{
				for (auto it = l.rbegin(); it != l.rend(); ++it)
				{
					output << *it;
				}
				CHECK(output.str() == "fourthreetwoone");
			}
		}

		WHEN("go through all the elements in the temporary range loop")
		{
			THEN("output should be contain all elements")
			{
				for (auto s : l)
				{
					output << s;
				}
				CHECK(output.str() == "onetwothreefour");
			}
		}
	}
}

std::string ListToString(const CStringList& l)
{
	std::string result;
	for (auto s : l)
	{
		result += s;
	}

	return result;
}

SCENARIO("push back and front testing")
{
	GIVEN("empty list")
	{
		CStringList l;

		WHEN("push back element and push front element")
		{
			l.PushBack("1");
			l.PushFront("2");
			THEN("second element should be first")
			{
				CHECK(ListToString(l) == "21");
			}

			AND_WHEN("push front element")
			{
				l.PushFront("3");
				THEN("new element should be first")
				{
					CHECK(ListToString(l) == "321");
				}

				AND_WHEN("push back element")
				{
					l.PushBack("4");
					THEN("new element should be last")
					{
						CHECK(ListToString(l) == "3214");
					}
				}
			}
		}
	}
}

SCENARIO("insert test")
{
	GIVEN("empty list")
	{
		CStringList l;

		WHEN("insert element to empty list by iterator begin")
		{
			auto it = l.begin();
			l.Insert(it, "A");
			THEN("list should be contain only this element")
			{
				CHECK(ListToString(l) == "A");
			}
		}

		WHEN("insert element to empty list by iterator end")
		{
			auto it = l.end();
			l.Insert(it, "A");
			THEN("list should be contain only this element")
			{
				CHECK(ListToString(l) == "A");
			}
		}
	}

	GIVEN("list with three element")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");

		WHEN("get an iterator pointing to the string 'A' and insert a new one in this place")
		{
			auto it = l.begin();
			CHECK(*it == "A");
			l.Insert(it, "T");
			THEN("new element must be inserted before the specified string")
			{
				CHECK(ListToString(l) == "TABC");
			}
		}

		WHEN("get an iterator pointing to the string 'B' and insert a new one in this place")
		{
			auto it = l.begin();
			it++;
			CHECK(*it == "B");
			l.Insert(it, "T");
			THEN("new element must be inserted before the specified string")
			{
				CHECK(ListToString(l) == "ATBC");
			}
		}

		WHEN("get an iterator pointing to the string 'C' and insert a new one in this place")
		{
			auto it = l.end();
			it--;
			CHECK(*it == "C");
			l.Insert(it, "T");
			THEN("new element must be inserted before the specified string")
			{
				CHECK(ListToString(l) == "ABTC");
			}
		}

		WHEN("get an end iterator and insert a new one in this place")
		{
			auto it = l.end();
			l.Insert(it, "T");
			THEN("new element must be inserted before end iterator")
			{
				CHECK(ListToString(l) == "ABCT");
			}
		}
	}
}

SCENARIO("testing erase")
{
	GIVEN("empty list")
	{
		CStringList l;

		WHEN("try to erase an element by the begin or end iterator")
		{
			auto it = l.begin();
			auto it2 = l.end();
			THEN("an exception should be thrown")
			{
				CHECK_THROWS_AS(l.Erase(it), std::logic_error);
				CHECK_THROWS_AS(l.Erase(it2), std::logic_error);
			}
		}
	}

	GIVEN("list with three element")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");

		WHEN("get an iterator pointing to the string 'A' and erase it")
		{
			auto it = l.begin();
			CHECK(*it == "A");
			l.Erase(it);
			THEN("element must be erased")
			{
				CHECK(ListToString(l) == "BC");
			}
		}

		WHEN("get an iterator pointing to the string 'B' and erase it")
		{
			auto it = l.begin();
			it++;
			CHECK(*it == "B");
			l.Erase(it);
			THEN("element must be erased")
			{
				CHECK(ListToString(l) == "AC");
			}
		}

		WHEN("get an iterator pointing to the string 'C' and erase it")
		{
			auto it = l.end();
			it--;
			CHECK(*it == "C");
			l.Erase(it);
			THEN("element must be erased")
			{
				CHECK(ListToString(l) == "AB");
			}
		}
	}
}

SCENARIO("testing copying constructor")
{
	GIVEN("empty list")
	{
		CStringList l;
		WHEN("create new list with other list in params")
		{
			CStringList newList(l);
			THEN("new list should be emty, size 0")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}
	}

	GIVEN("list with three elements")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");
		WHEN("create new list with other list in params")
		{
			CStringList newList(l);
			THEN("new list should be equal other list")
			{
				CHECK(ListToString(l) == ListToString(newList));
			}

			AND_WHEN("change element in first list")
			{
				auto it = l.begin();
				*it = "G";
				THEN("lists must be different")
				{
					CHECK(ListToString(l) != ListToString(newList));
					CHECK(ListToString(l) == "GBC");
					CHECK(ListToString(newList) == "ABC");
				}
			}

			AND_WHEN("change element in new list")
			{
				auto it = newList.begin();
				*it = "G";
				THEN("lists must be different")
				{
					CHECK(ListToString(l) != ListToString(newList));
					CHECK(ListToString(newList) == "GBC");
					CHECK(ListToString(l) == "ABC");
				}
			}
		}
	}
}

SCENARIO("testing assignment operator")
{
	GIVEN("empty list")
	{
		CStringList l;

		WHEN("assign an element to itself")
		{
			l = l;
			THEN("list should not change")
			{
				CHECK(l.IsEmpty());
				CHECK(l.GetSize() == 0);
			}
		}

		WHEN("create new list and assign first list to it")
		{
			CStringList newList;
			newList = l;
			THEN("new list should be emty, size 0")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}

		WHEN("create new list with elements and assign first list to it")
		{
			CStringList newList;
			newList.PushBack("A");
			newList.PushBack("B");
			newList = l;
			THEN("new list should be emty, size 0")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}
	}

	GIVEN("list with three elements")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");

		WHEN("assign an element to itself")
		{
			l = l;
			THEN("list should not change")
			{
				CHECK(ListToString(l) == "ABC");
			}
		}

		WHEN("create new list and assign first list to it")
		{
			CStringList newList;
			newList = l;
			THEN("new list should be equal other list")
			{
				CHECK(ListToString(l) == ListToString(newList));
			}

			AND_WHEN("change element in first list")
			{
				auto it = l.begin();
				*it = "G";
				THEN("lists must be different")
				{
					CHECK(ListToString(l) != ListToString(newList));
					CHECK(ListToString(l) == "GBC");
					CHECK(ListToString(newList) == "ABC");
				}
			}

			AND_WHEN("change element in new list")
			{
				auto it = newList.begin();
				*it = "G";
				THEN("lists must be different")
				{
					CHECK(ListToString(l) != ListToString(newList));
					CHECK(ListToString(newList) == "GBC");
					CHECK(ListToString(l) == "ABC");
				}
			}
		}

		WHEN("create new list with elements and assign first list to it")
		{
			CStringList newList;
			newList.PushBack("A");
			newList.PushBack("B");
			newList = l;
			THEN("new list should be equal other list")
			{
				CHECK(ListToString(l) == ListToString(newList));
			}
		}
	}
}

SCENARIO("testing move constructor")
{
	GIVEN("empty list")
	{
		CStringList l;
		WHEN("create new list with other list in params")
		{
			CStringList newList(std::move(l));
			THEN("new list should be emty, size 0")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}
	}

	GIVEN("list with three elements")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");
		WHEN("create new list with other list in params")
		{
			CStringList newList(std::move(l));
			THEN("new list should be an equal source list")
			{
				CHECK(ListToString(newList) == "ABC");
			}
		}
	}
}

SCENARIO("testing move assignment operator")
{
	GIVEN("empty list")
	{
		CStringList l;
		l = std::move(l);
		WHEN("assign an element to itself")
		{
			THEN("list should not change")
			{
				CHECK(l.IsEmpty());
				CHECK(l.GetSize() == 0);
			}
		}

		WHEN("create new list and assign first list to it")
		{
			CStringList newList;
			newList = std::move(l);
			THEN("new list should be an equal source list")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}

		WHEN("create new list with elements and assign first list to it")
		{
			CStringList newList;
			newList.PushBack("A");
			newList.PushBack("B");
			newList = std::move(l);
			THEN("new list should be an equal source list")
			{
				CHECK(newList.IsEmpty());
				CHECK(newList.GetSize() == 0);
			}
		}
	}

	GIVEN("list with three elements")
	{
		CStringList l;
		l.PushBack("A");
		l.PushBack("B");
		l.PushBack("C");

		WHEN("assign an element to itself")
		{
			l = std::move(l);
			THEN("list should not change")
			{
				CHECK(ListToString(l) == "ABC");
			}
		}

		WHEN("create new list and assign first list to it")
		{
			CStringList newList;
			newList = std::move(l);
			THEN("new list should be an equal source list")
			{
				CHECK(ListToString(newList) == "ABC");
			}
		}

		WHEN("create new list with elements and assign first list to it")
		{
			CStringList newList;
			newList.PushBack("E");
			newList.PushBack("G");
			newList = std::move(l);
			THEN("new list should be an equal source list")
			{
				CHECK(ListToString(newList) == "ABC");
			}
		}
	}
}