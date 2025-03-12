#include "HtmlDecode.h"
#include "Replacer.h"

void HtmlDecode(std::istream& input, std::ostream& output)
{
	Patterns patterns = {
			{{"&quot;" }, { "\"" }},
			{{"&apos;"},{"\'"}},
			{{"&lt;"},{"<"}},
			{{"&gt;"},{">"}},
			{{"&amp;"},{"&"}}
	};
	Replacer replacer(patterns);

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(input, line))
	{
		output << replacer.Replace(line);
		if (!input.eof())
		{
			output << "\n";
		}
	}
}