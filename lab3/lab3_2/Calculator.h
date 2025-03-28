#pragma once
#include "Function.h"
#include "Operand.h"
#include "Variable.h"
#include <map>
#include <optional>
#include <vector>

struct FunctionDTO
{
	std::string functionName;
	std::string firstOperandName;
	std::optional<std::string> secondOperandName;
	std::optional<Operation> operation;
};

class Calculator
{
public:
	void AddVariable(const std::string& variableName);
	void LetVariable(const std::string& variableName, double value);
	void LetVariable(const std::string& variableName, const std::string& operand);
	void AddFunction(const FunctionDTO& args);	
	bool IsExistOperand(const std::string& operandName);
	double GetValue(const std::string& operand);
	std::vector<std::pair<std::string, double>> GetVariables();
	std::vector<std::pair<std::string, double>> GetFunctions();

private:
	std::map<std::string, std::shared_ptr<Function>> m_functions;
	std::map<std::string, std::shared_ptr<Variable>> m_variables;
	std::shared_ptr<Operand> GetOperand(const std::string& operandName);
};