#include "CRectangle.h"
#include <cmath>
#include <sstream>

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

double CRectangle::GetArea()
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter()
{
	return GetWidth() * 2 + GetHeight() * 2;
}

std::string CRectangle::ToString()
{
	std::ostringstream strm;
	strm << "Rectangle ";
	strm << "area: " << GetArea();
	strm << ", perimeter: " << GetPerimeter();
	strm << ", outline color: " << std::hex << GetOutlineColor();
	strm << ", fill color: " << std::hex << GetFillColor();
	strm << ", width: " << std::hex << GetWidth();
	strm << ", height: " << std::hex << GetHeight();

	return strm.str();
}

uint32_t CRectangle::GetOutlineColor()
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor()
{
	return m_fillColor;
}

void CRectangle::SetOutlineColor(uint32_t color)
{
	m_outlineColor = color;
}

void CRectangle::SetFillColor(uint32_t color)
{
	m_fillColor = color;
}

CPoint CRectangle::GetLeftTop()
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom()
{
	return m_rightBottom;
}

double CRectangle::GetWidth()
{
	return std::abs(m_leftTop.x - m_rightBottom.x);
}

double CRectangle::GetHeight()
{
	return std::abs(m_leftTop.y - m_rightBottom.y);
}
