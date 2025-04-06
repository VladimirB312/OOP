#include "CLineSegment.h"
#include <cmath>
#include <sstream>

const double LINE_THICKNESS = 1;

CLineSegment::CLineSegment(CPoint start, CPoint end)
	: m_start(start)
	, m_end(end)
{
}

double CLineSegment::GetArea() const
{
	return m_start.GetDistanceTo(m_end);
}

double CLineSegment::GetPerimeter() const
{
	return GetArea() * 2 + LINE_THICKNESS * 2;
}

std::string CLineSegment::ToString() const
{
	return "Line segment " + Shape::ToString() + "\n";
}


CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_start, m_end, GetOutlineColor());
}
