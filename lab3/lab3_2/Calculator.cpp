#include "Calculator.h"
#include "CalculatorException.h"
#include "Function.h"
#include "Operand.h"
#include "Variable.h"
#include <algorithm>
#include <cmath>
#include <iterator>

bool Calculator::IsExistOperand(const std::string& operandName)
{
	return m_variables.contains(operandName) || m_functions.contains(operandName);
}

void Calculator::AddVariable(const std::string& variableName)
{
	if (!IsExistOperand(variableName))
	{
		m_variables[variableName] = std::make_shared<Variable>();
		return;
	}

	throw CalculatorException("Name already exists");
}

void Calculator::LetVariable(const std::string& variableName, double value)
{
	if (m_functions.contains(variableName))
	{
		throw CalculatorException("There is already a function with this name");
	}

	if (m_variables.contains(variableName))
	{
		m_variables[variableName]->SetValue(value);
		return;
	}

	m_variables[variableName] = std::make_shared<Variable>(value);
}

void Calculator::LetVariable(const std::string& variableName, const std::string& operand)
{
	LetVariable(variableName, GetOperand(operand)->GetValue());
}

std::shared_ptr<Operand> Calculator::GetOperand(const std::string& operandName)
{
	if (m_variables.contains(operandName))
	{
		return m_variables[operandName];
	}

	if (m_functions.contains(operandName))
	{
		return m_functions[operandName];
	}

	throw CalculatorException("Name does not exist");
}

void Calculator::AddFunction(const FunctionDTO& args)
{
	if (IsExistOperand(args.functionName))
	{
		throw CalculatorException("Name already exists");
	}

	if (!IsExistOperand(args.firstOperandName))
	{
		throw CalculatorException("Name does not exist");
	}

	if (!args.secondOperandName.has_value())
	{
		m_functions[args.functionName] = std::make_shared<Function>(GetOperand(args.firstOperandName));
		m_functions[args.functionName]->Subscribe();
		return;
	}

	if (!args.operation.has_value())
	{
		throw CalculatorException("Operator not passed");
	}

	m_functions[args.functionName] = std::make_shared<Function>(
		GetOperand(args.firstOperandName),
		GetOperand(args.secondOperandName.value()),
		args.operation.value());
	m_functions[args.functionName]->Subscribe();
}

double Calculator::GetValue(const std::string& operand)
{
	if (m_variables.contains(operand))
	{
		return m_variables[operand]->GetValue();
	}

	if (m_functions.contains(operand))
	{
		return m_functions[operand]->GetValue();
	}

	throw CalculatorException("Name does not exist");
}

std::vector<std::pair<std::string, double>> Calculator::GetFunctions()
{
	std::vector<std::pair<std::string, double>> result;
	std::transform(m_functions.begin(), m_functions.end(), std::back_inserter(result),
		[](const auto& pair) {
			return std::make_pair(pair.first, pair.second->GetValue());
		});

	return result;
}

std::vector<std::pair<std::string, double>> Calculator::GetVariables()
{
	std::vector<std::pair<std::string, double>> result;
	std::transform(m_variables.begin(), m_variables.end(), std::back_inserter(result),
		[](const auto& pair) {
			return std::make_pair(pair.first, pair.second->GetValue());
		});

	return result;
}