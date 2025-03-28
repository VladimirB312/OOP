#pragma once
#include "Calculator.h"
#include "IdentifiersParser.h"
#include <functional>
#include <map>
#include <sstream>

class CalculatorUI
{
public:
	CalculatorUI(std::istream& input, std::ostream& output);
	void Start();

private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	Calculator m_calculator;
	ActionMap m_actionMap;
	void HandleCommand(std::istream& args);
	void AddVariable(std::istream& args);
	void LetVariable(std::istream& args);
	void AddFunction(std::istream& args);
	void Print(std::istream& args);
	void PrintVariables(std::istream& args);
	void PrintFunctions(std::istream& args);
};