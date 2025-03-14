#include <numeric>
#include <sstream>
#include <stack>
#include <vector>

namespace symbol
{
const char ADDITION = '+';
const char MULTIPLICATION = '*';
const char MINUS = '-';
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';
} // namespace symbol

enum class Operation
{
	ADDITION,
	MULTIPLICATION
};

struct Expression
{
	Operation operation;
	std::vector<int> arguments;
};

int GetArgumentsSum(const std::vector<int>& args)
{
	return std::accumulate(args.begin(), args.end(), 0);
}

int GetArgumentsMultiplication(const std::vector<int>& args)
{
	return std::accumulate(args.begin(), args.end(), 1, std::multiplies<>());
}

int CalculateExpression(const Expression& expression)
{
	if (expression.arguments.empty())
	{
		throw std::runtime_error("Invalid expression");
	}

	if (expression.operation == Operation::ADDITION)
	{
		return GetArgumentsSum(expression.arguments);
	}

	if (expression.operation == Operation::MULTIPLICATION)
	{
		return GetArgumentsMultiplication(expression.arguments);
	}

	throw std::runtime_error("Unknown operation");
}

Operation CharToOperation(char ch)
{
	if (ch == symbol::ADDITION)
	{
		return Operation::ADDITION;
	}

	if (ch == symbol::MULTIPLICATION)
	{
		return Operation::MULTIPLICATION;
	}

	throw std::runtime_error("Invalid expression");
}

char ReadCh(std::istream& input)
{
	char ch;
	if (!(input >> ch))
	{
		throw std::runtime_error("Invalid expression");
	}

	return ch;
}

int ReadNumber(std::istream& input)
{
	int num;
	if (!(input >> num))
	{
		throw std::runtime_error("Invalid expression");
	}

	return num;
}

void AddNewExpression(std::istream& input, std::stack<Expression>& expressionStack)
{
	char ch = ReadCh(input);
	Expression expr{ CharToOperation(ch), {} };
	expressionStack.push(expr);
}

int EvaluateExpression(std::stack<Expression>& expressionStack)
{
	if (expressionStack.empty())
	{
		throw std::runtime_error("Invalid expression");
	}

	Expression expression = expressionStack.top();
	expressionStack.pop();

	return CalculateExpression(expression);
}

void AddArgument(std::stack<Expression>& expressionStack, int argument)
{
	if (expressionStack.empty())
	{
		throw std::runtime_error("Invalid expression");
	}

	expressionStack.top().arguments.push_back(argument);
}

bool IsEol(std::istream& input)
{
	char ch;
	if (!(input >> ch))
	{
		return true;
	}
	input.unget();

	return false;
}

int Calculate(std::istream& input)
{
	char ch;
	std::stack<Expression> expressionStack;
	while (input >> ch)
	{
		if (ch == symbol::OPEN_BRACKET)
		{
			AddNewExpression(input, expressionStack);
			continue;
		}
		if (ch == symbol::CLOSE_BRACKET)
		{
			int result = EvaluateExpression(expressionStack);

			if (IsEol(input))
			{
				return result;
			}

			AddArgument(expressionStack, result);
			continue;
		}

		input.unget();
		AddArgument(expressionStack, ReadNumber(input));
	}

	throw std::runtime_error("Invalid expression");
}