#include <iostream>
#include "Replacer.h"

void HtmlDecode()
{
	Patterns patterns = {
			{{"&quot;" }, { "\"" }},
			{{"&apos;"},{"\'"}},
			{{"&lt;"},{"<"}},
			{{"&gt;"},{">"}},
			{{"&amp;"},{"&"}}
	};
	AhoReplacer ahoReplacer(patterns);

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::cout << ahoReplacer.ReplaceMatches(line) << "\n";
	}
}

int main() {
	HtmlDecode();

	return 0;
}