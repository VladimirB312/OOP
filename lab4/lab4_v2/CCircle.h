#pragma once
#include "CPoint.h"
#include "SolidShape.h"
#include <optional>

class CCircle : public SolidShape
{
public:
	CCircle(CPoint center, double radius);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const; 
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};