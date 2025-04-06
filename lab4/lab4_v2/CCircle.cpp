#include "CCircle.h"
#include <sstream>

const double PI = 3.14159265358979323846;

CCircle::CCircle(CPoint center, double radius)
	: m_center(center)
	, m_radius(radius)
{
	if (m_radius <= 0)
	{
		throw ShapeException("radius cannot be negative");
	}
}

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

std::string CCircle::ToString() const
{
	return "Circle " + SolidShape::ToString() + "\n";
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

