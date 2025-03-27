#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Function.h"
#include "../Operand.h"
#include "../Variable.h"
#include <cmath>

SCENARIO("create variable")
{
	WHEN("create variable without value")
	{
		Variable x;
		THEN("varible value should be nan")
		{
			CHECK(std::isnan(x.GetValue()));
		}
		AND_WHEN("change variable value")
		{
			x.SetValue(5.5);
			THEN("variable value should be changed")
			{
				CHECK(x.GetValue() == 5.5);
			}
		}
	}

	WHEN("create variable with double value 1.5 in args")
	{
		Variable x(1.5);
		THEN("varible value should be 1.5")
		{
			CHECK(x.GetValue() == 1.5);
		}
		AND_WHEN("change variable value")
		{
			x.SetValue(5.5);
			THEN("variable value should be changed")
			{
				CHECK(x.GetValue() == 5.5);
			}
		}
	}
}

SCENARIO("create function")
{
	WHEN("create function with one variable")
	{
		Variable x(4);
		Function fn(x);
		THEN("the calculated value of this function must be equal to the variable")
		{
			CHECK(fn.GetValue() == x.GetValue());
		}
		AND_WHEN("change variable value")
		{
			x.SetValue(6);
			THEN("the calculated value of this function must be equal to the variable")
			{
				CHECK(fn.GetValue() == x.GetValue());
			}
		}
	}

	WHEN("create function with one empty variable")
	{
		Variable x;
		Function fn(x);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
		AND_WHEN("change variable value")
		{
			x.SetValue(6);
			THEN("the calculated value of this function must be equal to the variable")
			{
				CHECK(fn.GetValue() == x.GetValue());
			}
		}
	}

	WHEN("create function with two empty variables")
	{
		Variable x;
		Variable y;
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variable and first variable is empty")
	{
		Variable x;
		Variable y(4);
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variables and second variable is empty")
	{
		Variable x(4);
		Variable y;
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variables and operation addition")
	{
		Variable x(4);
		Variable y(2);
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be equal to the sum of the variables")
		{
			CHECK(fn.GetValue() == 6);
		}
		AND_WHEN("change the values of these variables")
		{
			x.SetValue(9);
			y.SetValue(3);
			THEN("the calculated value of the function should also change")
			{
				CHECK(fn.GetValue() == 12);
			}
		}
	}

	WHEN("create function with two variables and operation multiplication")
	{
		Variable x(4);
		Variable y(2);
		Function fn(x, y, Operation::MULTIPLICATION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 8);
		}
	}

	WHEN("create function with two variables and operation subtraction")
	{
		Variable x(4);
		Variable y(2);
		Function fn(x, y, Operation::SUBTRACTION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 2);
		}
	}

	WHEN("create function with two variables and operation division")
	{
		Variable x(4);
		Variable y(2);
		Function fn(x, y, Operation::DIVISION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 2);
		}
	}

	WHEN("create function with two variables, second variable is 0 and operation division")
	{
		Variable x(4);
		Variable y(0);
		Function fn(x, y, Operation::DIVISION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	GIVEN("created function with one variable")
	{
		Variable x(4);
		Function fnOne(x);
		WHEN("create a function that takes this function as argument")
		{
			Function fnTwo(fnOne);
			THEN("the calculated value of this function must be equal first function")
			{
				CHECK(fnOne.GetValue() == fnTwo.GetValue());
			}
		}
		WHEN("create a function that takes this function and variable as arguments and operation addition")
		{
			Function fnTwo(fnOne, x, Operation::ADDITION);
			THEN("the calculated value of this function must be equal sum first function and variable")
			{
				CHECK(fnTwo.GetValue() == 8);
			}
			AND_WHEN("change variable value")
			{
				x.SetValue(10);
				THEN("the calculated value of this function must be also change")
				{
					CHECK(fnTwo.GetValue() == 20);
				}
			}
		}
	}

	GIVEN("created function with two variable and operation addition")
	{
		Variable x(4);
		Variable y(2);
		Function fnOne(x, y, Operation::ADDITION);
		WHEN("create a function that takes this function as argument")
		{
			Function fnTwo(fnOne);
			THEN("the calculated value of this function must be equal first function")
			{
				CHECK(fnOne.GetValue() == fnTwo.GetValue());
			}
		}
		WHEN("create a function that takes this function and variable as arguments and operation addition")
		{
			Function fnTwo(fnOne, x, Operation::ADDITION);
			THEN("the calculated value of this function must be equal sum first function and variable")
			{
				CHECK(fnTwo.GetValue() == 10);
			}
		}
		WHEN("create a function that takes two function as arguments with operation addition")
		{
			Variable i(5);
			Variable j(3);
			Function fnTwo(i, j, Operation::ADDITION);
			Function fnThree(fnOne, fnTwo, Operation::ADDITION);
			THEN("the calculate value of this function must me equal sum of first and second functions")
			{
				CHECK(fnThree.GetValue() == 14);
			}
		}
	}
}