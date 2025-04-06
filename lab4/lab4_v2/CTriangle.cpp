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

double CTriangle::GetArea() const
{
	return m_area;
}

double CTriangle::GetPerimeter() const
{
	return m_perimeter;
}

std::string CTriangle::ToString() const
{
	return "Triangle " + SolidShape::ToString() + "\n";
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawPolygon({ m_vertex1, m_vertex2, m_vertex3 }, GetOutlineColor(), GetFillColor());
}

void CTriangle::CalculateProperties()
{
	double p1 = m_vertex1.GetDistanceTo(m_vertex2);
	double p2 = m_vertex2.GetDistanceTo(m_vertex3);
	double p3 = m_vertex3.GetDistanceTo(m_vertex1);

	CheckValidTriangle(p1, p2, p3);

	m_perimeter = p1 + p2 + p3;

	double semiP = m_perimeter / 2;

	m_area = std::sqrt(semiP * (semiP - p1) * (semiP - p2) * (semiP - p3));
}
