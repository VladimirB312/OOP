#include "SolidShape.h"
#include <sstream>
#include <format>

uint32_t SolidShape::GetFillColor() const
{
	return m_fillColor;
}

void SolidShape::SetFillColor(uint32_t color)
{
	m_fillColor = color;
}

std::string SolidShape::ToString() const
{
	std::ostringstream strm;
	strm << std::format(", fill color 0x{:06X}", m_fillColor);

	return Shape::ToString() + strm.str();
}