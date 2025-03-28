#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator.h"
#include "../CalculatorException.h"
#include "../Function.h"
#include "../Operand.h"
#include "../Variable.h"
#include <cmath>

SCENARIO("create variable")
{
	WHEN("create variable without value")
	{
		auto x = std::make_shared<Variable>();
		THEN("variable value should be nan")
		{
			CHECK(std::isnan(x->GetValue()));
		}

		AND_WHEN("change variable value")
		{
			x->SetValue(5.5);
			THEN("variable value should be changed")
			{
				CHECK(x->GetValue() == 5.5);
			}
		}
	}

	WHEN("create variable with double value 1.5 in args")
	{
		auto x = std::make_shared<Variable>(1.5);
		THEN("variable value should be 1.5")
		{
			CHECK(x->GetValue() == 1.5);
		}

		AND_WHEN("change variable value")
		{
			x->SetValue(5.5);
			THEN("variable value should be changed")
			{
				CHECK(x->GetValue() == 5.5);
			}
		}
	}
}

SCENARIO("create function")
{
	WHEN("create function with one variable")
	{
		auto x = std::make_shared<Variable>(4);
		Function fn(x);
		THEN("the calculated value of this function must be equal to the variable")
		{
			CHECK(fn.GetValue() == x->GetValue());
		}

		AND_WHEN("change variable value")
		{
			x->SetValue(6);
			THEN("the calculated value of this function must be equal to the variable")
			{
				CHECK(fn.GetValue() == x->GetValue());
			}
		}
	}

	WHEN("create function with one empty variable")
	{
		auto x = std::make_shared<Variable>();
		Function fn(x);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}

		AND_WHEN("change variable value")
		{
			x->SetValue(6);
			THEN("the calculated value of this function must be equal to the variable")
			{
				CHECK(fn.GetValue() == x->GetValue());
			}
		}
	}

	WHEN("create function with two empty variables")
	{
		auto x = std::make_shared<Variable>();
		auto y = std::make_shared<Variable>();
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variable and first variable is empty")
	{
		auto x = std::make_shared<Variable>();
		auto y = std::make_shared<Variable>(4);
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variables and second variable is empty")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>();
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be nan")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	WHEN("create function with two variables and operation addition")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(2);
		Function fn(x, y, Operation::ADDITION);
		THEN("the calculated value of this function must be equal to the sum of the variables")
		{
			CHECK(fn.GetValue() == 6);
		}

		AND_WHEN("change the values of these variables")
		{
			x->SetValue(9);
			y->SetValue(3);
			THEN("the calculated value of the function should also change")
			{
				CHECK(fn.GetValue() == 12);
			}
		}
	}

	WHEN("create function with two variables and operation multiplication")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(2);
		Function fn(x, y, Operation::MULTIPLICATION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 8);
		}
	}

	WHEN("create function with two variables and operation subtraction")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(2);
		Function fn(x, y, Operation::SUBTRACTION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 2);
		}
	}

	WHEN("create function with two variables and operation division")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(2);
		Function fn(x, y, Operation::DIVISION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(fn.GetValue() == 2);
		}
	}

	WHEN("create function with two variables, second variable is 0 and operation division")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(0);
		Function fn(x, y, Operation::DIVISION);
		THEN("the calculated value of this function must be equal to the multiplication of the variables")
		{
			CHECK(std::isnan(fn.GetValue()));
		}
	}

	GIVEN("created function with one variable")
	{
		auto x = std::make_shared<Variable>(4);
		auto fnOne = std::make_shared<Function>(x);
		WHEN("create a function that takes this function as argument")
		{
			Function fnTwo(fnOne);
			THEN("the calculated value of this function must be equal first function")
			{
				CHECK(fnOne->GetValue() == fnTwo.GetValue());
			}
		}

		WHEN("create a function that takes this function and variable as arguments and operation addition")
		{
			auto fnTwo = std::make_shared<Function>(fnOne, x, Operation::ADDITION);
			THEN("the calculated value of this function must be equal sum first function and variable")
			{
				CHECK(fnTwo->GetValue() == 8);
			}

			AND_WHEN("change variable value")
			{
				x->SetValue(10);
				THEN("the calculated value of this function must be also change")
				{
					CHECK(fnTwo->GetValue() == 20);
				}
			}
		}
	}

	GIVEN("created function with two variable and operation addition")
	{
		auto x = std::make_shared<Variable>(4);
		auto y = std::make_shared<Variable>(2);
		auto fnOne = std::make_shared<Function>(x, y, Operation::ADDITION);
		WHEN("create a function that takes this function as argument")
		{
			Function fnTwo(fnOne);
			THEN("the calculated value of this function must be equal first function")
			{
				CHECK(fnOne->GetValue() == fnTwo.GetValue());
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
			auto i = std::make_shared<Variable>(5);
			auto j = std::make_shared<Variable>(3);
			auto fnTwo = std::make_shared<Function>(i, j, Operation::ADDITION);
			Function fnThree(fnOne, fnTwo, Operation::ADDITION);
			THEN("the calculate value of this function must me equal sum of first and second functions")
			{
				CHECK(fnThree.GetValue() == 14);
			}
		}
	}
}

SCENARIO("Calculator testing")
{
	GIVEN("calculator without operands")
	{
		Calculator calculator;
		WHEN("add new variable without value")
		{
			calculator.AddVariable("x");
			THEN("this variable should be added and have the value nan")
			{
				CHECK(calculator.IsExistOperand("x"));
				CHECK(std::isnan(calculator.GetValue("x")));
			}

			AND_WHEN("add another variable without a value and assign it the value of the first variable")
			{
				calculator.LetVariable("y", "x");
				THEN("this variable should be added and have the value nan")
				{
					CHECK(std::isnan(calculator.GetValue("y")));
				}
			}

			AND_WHEN("let a value for this variable")
			{
				calculator.LetVariable("x", 10);
				THEN("this variable must have this value")
				{
					CHECK(calculator.GetValue("x") == 10);
				}

				AND_WHEN("let a new value for this variable")
				{
					calculator.LetVariable("x", 20);
					THEN("this variable must have this value")
					{
						CHECK(calculator.GetValue("x") == 20);
					}
				}
			}

			AND_WHEN("try to create a variable with the same name")
			{
				THEN("should get a calculator exception error")
				{
					CHECK_THROWS_AS(calculator.AddVariable("x"), CalculatorException);
				}
			}
		}

		WHEN("add new variable with value")
		{
			calculator.LetVariable("x", 10);
			THEN("this variable should be added and have this value")
			{
				CHECK(calculator.GetValue("x") == 10);
			}

			AND_WHEN("add another variable without a value and assign it the value of the first variable")
			{
				calculator.LetVariable("y", "x");
				THEN("this variable should be added and have the value of the first variable")
				{
					CHECK(calculator.GetValue("y") == 10);
				}

				AND_WHEN("change the value of the second variable and assign it to the first one")
				{
					calculator.LetVariable("y", 15);
					calculator.LetVariable("x", "y");
					THEN("first variable should have the value of the second variable")
					{
						CHECK(calculator.GetValue("x") == 15);
					}
				}
			}
		}

		WHEN("let's try to add a function with non-existent first operand name")
		{
			THEN("should get a calculator exception error")
			{
				CHECK_THROWS_AS(calculator.AddFunction({ "fn1", "x" }), CalculatorException);
			}
		}

		WHEN("let's try to add a function with non-existent second operand name")
		{
			calculator.LetVariable("x", 5);
			THEN("should get a calculator exception error")
			{
				CHECK_THROWS_AS(calculator.AddFunction({ "fn1", "x", "y", Operation::ADDITION }), CalculatorException);
			}
		}

		WHEN("let's try to add a function with non-existent all operands name")
		{
			THEN("should get a calculator exception error")
			{
				CHECK_THROWS_AS(calculator.AddFunction({ "fn1", "x", "y", Operation::ADDITION }), CalculatorException);
			}
		}

		WHEN("let's try to add a function with non-existent operation")
		{
			calculator.LetVariable("x", 5);
			calculator.LetVariable("y", 10);
			THEN("should get a calculator exception error")
			{
				CHECK_THROWS_AS(calculator.AddFunction({ "fn1", "x", "y" }), CalculatorException);
			}
		}

		WHEN("add a function with one operand with nan value")
		{
			calculator.AddVariable("x");
			calculator.AddFunction({ "fn1", "x" });
			THEN("this function should be added and have the value of nan")
			{
				CHECK(std::isnan(calculator.GetValue("fn1")));
			}

			AND_WHEN("try to add a function with an existing name")
			{
				THEN("should get a calculator exception error")
				{
					CHECK_THROWS_AS(calculator.AddFunction({ "fn1", "x" }), CalculatorException);
				}
			}

			AND_WHEN("change the value of a variable")
			{
				calculator.LetVariable("x", 15);
				THEN("function should have the value of this variable")
				{
					CHECK(calculator.GetValue("fn1") == 15);
				}

				AND_WHEN("add a new function with two variable operands and operation addition")
				{
					calculator.LetVariable("v1", 20);
					calculator.LetVariable("v2", 30);
					calculator.AddFunction({ "fn2", "v1", "v2", Operation::ADDITION });
					THEN("function should have sum of this variables")
					{
						CHECK(calculator.GetValue("fn2") == 50);
					}

					AND_WHEN("add a new function with two function operands and operation addition")
					{
						calculator.AddFunction({ "fn3", "fn1", "fn2", Operation::ADDITION });
						THEN("function should have sum of this function values")
						{
							CHECK(calculator.GetValue("fn3") == 65);
						}

						AND_WHEN("change variables value")
						{
							calculator.LetVariable("x", 30);
							calculator.LetVariable("v1", 25);
							calculator.LetVariable("v2", 12);
							THEN("all functions containing these variables must update their values")
							{
								CHECK(calculator.GetValue("fn1") == 30);
								CHECK(calculator.GetValue("fn2") == 37);
								CHECK(calculator.GetValue("fn3") == 67);
							}
						}
					}
				}
			}
		}
	}
}