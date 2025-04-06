#pragma once
#include "CPoint.h"
#include "SolidShape.h"
#include <optional>

class CCircle : public SolidShape
{
public:
	CCircle(CPoint center, double radius);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CPoint GetCenter();
	double GetRadius();

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_fillColor = 0xFFFFFFFF;
};