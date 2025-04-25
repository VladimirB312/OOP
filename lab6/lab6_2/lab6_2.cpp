#include <iostream>
#include <list>

#include "CStringList.h"

void PrintLi(const CStringList& li)
{
	std::cout << "li = ";
	for (const auto& s : li)
	{
		std::cout << s;
	}
	std::cout << "\n";
}

int main()
{
	CStringList l;

	try
	{
		l.PushBack("1");
		l.PushBack("2");
		l.PushBack("3");
		l.PushBack("4");
		l.PushFront("f1");
		l.PushFront("f2");
		l.PushFront("f3");
		CStringList l2;
		l2 = l;
		{
			CStringList l3(l2);
			auto it = l3.begin();
			*it = "asd";
		}
		auto it = l.begin();
		*it = "A0";
		for (const auto s : l)
		{
			std::cout << s;
		}

		std::cout << "\n";

		for (const auto s : l2)
		{
			std::cout << s;
		}
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "BAD ALLOC!";
		std::cout << e.what();
	}
	catch (...)
	{
		std::cout << "NOT BAD ALLOC EX";
		return 1;
	};
	std::cout << "\n";
	{
		CStringList li;
		li.PushBack("A1");
		li.PushBack("A2");
		li.PushBack("A3");
		li.PushBack("A4");
		li.PushBack("A5");
		PrintLi(li);

		auto it = li.begin();
		li.Erase(it);
		PrintLi(li);
		it = --li.end();
		li.Insert(it, "N");
		PrintLi(li);
	}

	return 0;
}
