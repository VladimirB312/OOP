#include "CalculatorUI.h"
#include "CalculatorException.h"
#include "CalculatorUIException.h"
#include "ParserException.h"

#include <iomanip>
#include <regex>
#include <string>

namespace
{
Operation StringToOperation(const std::string& op)
{
	if (op == "+")
	{
		return Operation::ADDITION;
	}
	if (op == "*")
	{
		return Operation::MULTIPLICATION;
	}
	if (op == "-")
	{
		return Operation::SUBTRACTION;
	}
	if (op == "/")
	{
		return Operation::DIVISION;
	}
	throw CalculatorException("Invalid usage");
}
} // namespace

namespace command
{
const std::string var = "var";
const std::string let = "let";
const std::string fn = "fn";
const std::string print = "print";
const std::string printvars = "printvars";
const std::string printfns = "printfns";
} // namespace command

CalculatorUI::CalculatorUI(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { command::var, [this](std::istream& strm) { return AddVariable(strm); } },
		  { command::let, [this](std::istream& strm) { return LetVariable(strm); } },
		  { command::fn, [this](std::istream& strm) { return AddFunction(strm); } },
		  { command::print, [this](std::istream& strm) { return Print(strm); } },
		  { command::printvars, [this](std::istream& strm) { return PrintVariables(strm); } },
		  { command::printfns, [this](std::istream& strm) { return PrintFunctions(strm); } } })
{
}

void CalculatorUI::Start()
{
	std::string line;
	while (getline(m_input, line))
	{
		std::istringstream strm(line);
		try
		{
			HandleCommand(strm);
		}
		catch (const CalculatorException& ex)
		{
			m_output << ex.what() << '\n';
		}
		catch (const CalculatorUIException& ex)
		{
			m_output << ex.what() << '\n';
		}
		catch (const ParserException& ex)
		{
			m_output << ex.what() << '\n';
		}
		catch (...)
		{
			throw;
		}
	}
}

void CalculatorUI::HandleCommand(std::istream& args)
{
	std::string action;
	args >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(args);
		return;
	}

	throw CalculatorUIException("Unknown command");
}

void CalculatorUI::AddVariable(std::istream& args)
{
	std::string varName;
	args >> varName;
	if (!IsValidIdentifier(varName))
	{
		throw CalculatorUIException("Invalid usage (AddVariable)");
	}

	m_calculator.AddVariable(varName);
}

void CalculatorUI::LetVariable(std::istream& args)
{
	Declaration declaration = ParseIdentifiers(args);

	if (!IsValidIdentifier(declaration.firstIdentifier))
	{
		throw CalculatorUIException("Invalid usage (LetVariable)");
	}

	if (IsValidIdentifier(declaration.secondIdentifier))
	{
		m_calculator.LetVariable(declaration.firstIdentifier, declaration.secondIdentifier);
		return;
	}

	m_calculator.LetVariable(declaration.firstIdentifier, StringToDouble(declaration.secondIdentifier));
}

void CalculatorUI::AddFunction(std::istream& args)
{
	Declaration declaration = ParseIdentifiers(args);
	if (!IsValidIdentifier(declaration.firstIdentifier) || !IsValidIdentifier(declaration.secondIdentifier))
	{
		throw CalculatorUIException("Invalid usage (AddFunction, invalid first or second identifier)");
	}

	if (!declaration.thirdIdentifier.has_value())
	{
		m_calculator.AddFunction({ declaration.firstIdentifier, declaration.secondIdentifier });
		return;
	}

	if (!IsValidIdentifier(declaration.thirdIdentifier.value()))
	{
		throw CalculatorUIException("Invalid usage (AddFunction, invalid third identifier)");
	}

	Operation opeartion = StringToOperation(declaration.operation.value());

	m_calculator.AddFunction({ declaration.firstIdentifier,
		declaration.secondIdentifier,
		declaration.thirdIdentifier.value(),
		opeartion });
}

void CalculatorUI::Print(std::istream& args)
{
	std::string identifier;
	args >> identifier;
	m_output << std::fixed << std::setprecision(2) << m_calculator.GetValue(identifier) << '\n';
}

void CalculatorUI::PrintVariables(std::istream& args)
{
	std::vector<std::pair<std::string, double>> variables = m_calculator.GetVariables();
	for (const auto& [key, value] : variables)
	{
		m_output << std::fixed << std::setprecision(2) << key << ":" << value << '\n'; 
	}
}

void CalculatorUI::PrintFunctions(std::istream& args)
{
	std::vector<std::pair<std::string, double>> variables = m_calculator.GetFunctions();
	for (const auto& [key, value] : variables)
	{
		m_output << std::fixed << std::setprecision(2) << key << ":" << value << '\n';
	}
}
