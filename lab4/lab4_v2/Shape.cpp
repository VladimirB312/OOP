#include "Shape.h"
#include <sstream>
#include <format>

uint32_t Shape::GetOutlineColor() const
{
	return m_outlineColor;
}

void Shape::SetOutlineColor(uint32_t color)
{
	m_outlineColor = color;
}

std::string Shape::ToString() const
{
	std::ostringstream strm;
	strm << "area : " << GetArea();
	strm << ", perimeter " << GetPerimeter();
	strm << ", perimeter " << GetPerimeter();
	strm << std::format(", outline color 0x{:06X}", m_outlineColor);
		
	return strm.str();
}
