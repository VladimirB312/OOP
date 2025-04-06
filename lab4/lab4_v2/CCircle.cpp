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

double CCircle::GetArea()
{
	return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter()
{
	return 2 * PI * m_radius;
}

std::string CCircle::ToString()
{
	std::ostringstream strm;
	strm << "Circle ";
	strm << "area: " << GetArea();
	strm << ", perimeter: " << GetPerimeter();
	strm << ", outline color: " << std::hex << GetOutlineColor();
	strm << ", fill color: " << std::hex << GetFillColor();

	return strm.str();
}

CPoint CCircle::GetCenter()
{
	return m_center;
}

double CCircle::GetRadius()
{
	return m_radius;
}

