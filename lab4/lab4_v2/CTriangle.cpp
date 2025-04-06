#include "CTriangle.h"
#include <cmath>
#include <sstream>

namespace
{
void CheckValidTriangle(double p1, double p2, double p3)
{
	if (p1 + p2 <= p3 || p2 + p3 <= p1 || p3 + p1 <= p2)
	{
		throw ShapeException("invalid triangle");
	}
}
} // namespace

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
	CalculateProperties();
}

double CTriangle::GetArea()
{
	if (!m_area.has_value())
	{
		CalculateProperties();
	}

	return m_area.value();
}

double CTriangle::GetPerimeter()
{
	if (!m_perimeter.has_value())
	{
		CalculateProperties();
	}

	return m_perimeter.value();
}

std::string CTriangle::ToString()
{
	std::ostringstream strm;
	strm << "Triangle ";
	strm << "area: " << GetArea();
	strm << ", perimeter: " << GetPerimeter();
	strm << ", outline color: " << std::hex << GetOutlineColor();
	strm << ", fill color: " << std::hex << GetFillColor();

	return strm.str();
}


CPoint CTriangle::GetVertex1()
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2()
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3()
{
	return m_vertex3;
}

void CTriangle::CalculateProperties()
{
	double p1 = m_vertex1.GetDistanceTo(m_vertex2);
	double p2 = m_vertex2.GetDistanceTo(m_vertex3);
	double p3 = m_vertex3.GetDistanceTo(m_vertex1);

	CheckValidTriangle(p1, p2, p3);

	m_perimeter = p1 + p2 + p3;

	double semiP = m_perimeter.value() / 2;

	m_area = std::sqrt(semiP * (semiP - p1) * (semiP - p2) * (semiP - p3));
}
