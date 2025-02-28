#include "HtmlDecode.h"

std::string HtmlDecode(std::string html)
{
	if (html == "&quot;")
	{
		html = "\"";
	}

	return html;
}
