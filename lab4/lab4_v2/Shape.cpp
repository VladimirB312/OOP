#include "Shape.h"

uint32_t Shape::GetOutlineColor()
{
	return m_outlineColor;
}

void Shape::SetOutlineColor(uint32_t color)
{
	m_outlineColor = color;
}

std::string Shape::GetInfo()
{

	return "area: " + std::to_string(GetArea()) + ", perimeter " + std::to_string(GetPerimeter()) + ", outline color" + std::to_string(GetOutlineColor());
}
