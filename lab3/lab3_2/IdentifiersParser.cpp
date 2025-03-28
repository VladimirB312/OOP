#include "IdentifiersParser.h"
#include "ParserException.h"
#include <regex>
#include <stdexcept>

const std::string OPERATORS = "+-*/";

std::string Trim(const std::string& str, char ch)
{
	std::string result;
	size_t start = str.find_first_not_of(ch);
	if (start == std::string::npos)
	{
		return result;
	}

	size_t finish = str.find_last_not_of(ch);
	result.append(str, start, finish - start + 1);

	return result;
}

bool IsValidIdentifier(const std::string& str)
{
	std::regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
	return std::regex_match(str, identifierRegex);
}

double StringToDouble(const std::string& str)
{
	double result;
	std::stringstream strm(str);
	strm >> result;

	if (!strm.fail() && strm.eof())
	{
		return result;
	}

	throw ParserException("Invalid usage");
}

Declaration ParseIdentifiers(std::istream& strm)
{
	std::string expression;
	if (!std::getline(strm, expression))
	{
		throw ParserException("Invalid usage");
	}

	size_t equalPos = expression.find("=");
	if (equalPos == std::string::npos)
	{
		throw ParserException("Invalid usage");
	}

	std::string firstIdentifier;
	firstIdentifier.append(expression, 0, equalPos);

	std::string secondIdentifier;
	size_t operatorPos = expression.find_first_of(OPERATORS);
	if (operatorPos == std::string::npos)
	{
		secondIdentifier.append(expression, equalPos + 1, expression.size());

		return Declaration{ Trim(firstIdentifier, ' '), Trim(secondIdentifier, ' ') };
	}

	secondIdentifier.append(expression, equalPos + 1, operatorPos - equalPos - 1);
	std::string thirdIdentifier;
	std::string operation;
	thirdIdentifier.append(expression, operatorPos + 1, expression.size() - operatorPos - 1);
	operation.append(expression, operatorPos, 1);

	return Declaration{
		Trim(firstIdentifier, ' '),
		Trim(secondIdentifier, ' '),
		Trim(thirdIdentifier, ' '),
		operation
	};
}