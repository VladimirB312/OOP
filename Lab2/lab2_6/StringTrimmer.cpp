#include "StringTrimmer.h"

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