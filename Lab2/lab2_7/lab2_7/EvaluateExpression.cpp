#include "EvaluateExpression.h"

const char PLUS_OP = '+';
const char MULTI_OP = '*';
const char UNARY_MINUS = '-';
const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';

void CheckOperator(char ch)
{
	if (ch != PLUS_OP && ch != MULTI_OP)
	{
		throw std::runtime_error("invalid expression");
	}
}

void CheckCloseBracket(char ch)
{
	if (ch != CLOSE_BRACKET)
	{
		throw std::runtime_error("invalid expression");
	}
}

int PerformOperation(int x1, int x2, char op)
{
	if (op == PLUS_OP)
	{
		return x1 + x2;
	}
	if (op == MULTI_OP)
	{
		return x1 * x2;
	}
}

int ParseNumber(std::istream& input, char& ch)
{
	bool isPositive = false;

	if (ch != UNARY_MINUS)
	{
		isPositive = true;
		input.unget();
	}

	int num;
	if (!(input >> num))
	{
		throw std::runtime_error("invalid expression");
	}

	return isPositive ? num : -num;
}

char ReadChar(std::istream& input)
{
	char ch;
	if (!(input >> ch))
	{
		throw std::runtime_error("invalid expression");
	}

	return ch;
}

int EvaluateExpression(std::istream& input)
{
	char ch = ReadChar(input);
	if (ch == OPEN_BRACKET)
	{
		ch = ReadChar(input);
		CheckOperator(ch);
		char op = ch;
		int num = EvaluateExpression(input);
		ch = ReadChar(input);
		while (!input.eof() && ch != CLOSE_BRACKET)
		{
			input.unget();
			num = PerformOperation(num, EvaluateExpression(input), op);
			ch = ReadChar(input);
		}

		CheckCloseBracket(ch);

		return num;
	}

	return ParseNumber(input, ch);
}