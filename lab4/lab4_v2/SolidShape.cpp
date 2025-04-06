#include "SolidShape.h"

uint32_t SolidShape::GetFillColor()
{
	return m_fillColor;
}

void SolidShape::SetFillColor(uint32_t color)
{
	m_fillColor = color;
}

std::string SolidShape::GetInfo()
{
	return Shape::GetInfo() + ", fill color: " + std::to_string(GetFillColor());
}
