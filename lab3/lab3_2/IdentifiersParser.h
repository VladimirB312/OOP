#pragma once
#include <sstream>
#include <optional>

struct Declaration
{
	std::string firstIdentifier;
	std::string secondIdentifier;
	std::optional<std::string> thirdIdentifier;
	std::optional<std::string> operation;
};

Declaration ParseIdentifiers(std::istream& args);
bool IsValidIdentifier(const std::string& str);
double StringToDouble(const std::string& str);