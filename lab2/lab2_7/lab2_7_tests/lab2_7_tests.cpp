#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../lab2_7/EvaluateExpression.h"

SCENARIO("Evaluate invalid expression")
{
	WHEN("expression is empty")
	{
		std::istringstream input("");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression contains only brackets")
	{
		std::istringstream input("()");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression not contains operations")
	{
		std::istringstream input("(7)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression not contains numbers")
	{
		std::istringstream input("(+)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression contains invalid operator")
	{
		std::istringstream input("(/ 7 2)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression contains extra closing brackets")
	{
		std::istringstream input("(+7))");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression contains extra opening brackets")
	{
		std::istringstream input("((+7)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("the order in an expression is not correct")
	{
		std::istringstream input("(7 + 2)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("the order in an expression is not correct")
	{
		std::istringstream input("(7 2 +)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression contains invalid arguments")
	{
		std::istringstream input("(+ a 7)");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}

	WHEN("expression not contains brackets")
	{
		std::istringstream input("+ 2 7");
		THEN("error is expected")
		{
			CHECK_THROWS_AS(Calculate(input), std::runtime_error);
		}
	}
}

SCENARIO("Evaluate valid expression")
{
	WHEN("expression contain only one number and operation plus")
	{
		std::istringstream input("(+ 7)");
		THEN("output must contain only this number")
		{
			CHECK(Calculate(input) == 7);
		}
	}

	WHEN("expression contain only one negative number and operation plus")
	{
		std::istringstream input("(+ -7)");
		THEN("output must contain only this number")
		{
			CHECK(Calculate(input) == -7);
		}
	}

	WHEN("expression contain only one number and operation multiply")
	{
		std::istringstream input("(* 8)");
		THEN("output must contain only this number")
		{
			CHECK(Calculate(input) == 8);
		}
	}

	WHEN("expression contain two numbers and operation plus")
	{
		std::istringstream input("(+ 2 3)");
		THEN("output must contain sum these numbers")
		{
			CHECK(Calculate(input) == 5);
		}
	}

	WHEN("expression contain three numbers and operation plus")
	{
		std::istringstream input("(+ 2 3 4)");
		THEN("output must contain sum these numbers")
		{
			CHECK(Calculate(input) == 9);
		}
	}

	WHEN("expression contain two numbers and operation multiply")
	{
		std::istringstream input("(* 2 4)");
		THEN("output must contain sum these numbers")
		{
			CHECK(Calculate(input) == 8);
		}
	}

	WHEN("expression contains within expression and the brackets start immediately after the operation")
	{
		std::istringstream input("(+ (* 2 3) (* 3 4))");
		THEN("output must contain result this expression")
		{
			CHECK(Calculate(input) == 18);
		}
	}

	WHEN("expression contains within expression and the brackets start immediately after the operation")
	{
		std::istringstream input("(* (+ 1 2) (+ 3 1))");
		THEN("output must contain result this expression")
		{
			CHECK(Calculate(input) == 12);
		}
	}

	WHEN("expression contains some expressions")
	{
		std::istringstream input("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))");
		THEN("output must contain result this expression")
		{
			CHECK(Calculate(input) == 33);
		}
	}

	WHEN("expression contains negative number")
	{
		std::istringstream input("(+ -2 3)");
		THEN("output must contain result this expression")
		{
			CHECK(Calculate(input) == 1);
		}
	}
}