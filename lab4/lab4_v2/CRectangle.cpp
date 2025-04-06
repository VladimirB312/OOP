#include "CRectangle.h"
#include <cmath>
#include <sstream>

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return GetWidth() * 2 + GetHeight() * 2;
}
	
std::string CRectangle::ToString() const
{
	std::ostringstream strm;	
	strm << ", width: " << GetWidth();
	strm << ", height: " << GetHeight();	

	return "Rectangle " + SolidShape::ToString() + strm.str() + "\n";
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return std::abs(m_leftTop.x - m_rightBottom.x);
}

double CRectangle::GetHeight() const
{
	return std::abs(m_leftTop.y - m_rightBottom.y);
}
