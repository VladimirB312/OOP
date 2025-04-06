#include "CLineSegment.h"
#include <cmath>
#include <sstream>

const double LINE_THICKNESS = 1;

CLineSegment::CLineSegment(CPoint start, CPoint end)
	: m_start(start)
	, m_end(end)
{
}

double CLineSegment::GetArea()
{
	return m_start.GetDistanceTo(m_end);
}

double CLineSegment::GetPerimeter()
{
	return GetArea() * 2 + LINE_THICKNESS * 2;
}

std::string CLineSegment::ToString()
{
	std::ostringstream strm;
	strm << "Line ";
	strm << "area: " << GetArea();
	strm << ", perimeter: " << GetPerimeter();
	strm << ", outline color: " << std::hex << GetOutlineColor();

	return strm.str();
}


CPoint CLineSegment::GetStartPoint()
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint()
{
	return m_end;
}
