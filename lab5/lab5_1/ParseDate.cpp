#include "ParseDate.h"

bool ParseDate(const std::string& date, int& day, int& month, int& year)
{
	std::regex pattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
	std::smatch match;

	if (std::regex_match(date, match, pattern))
	{
		day = std::stoi(match[1].str());
		month = std::stoi(match[2].str());
		year = std::stoi(match[3].str());

		return true;
	}

	return false;
}