#pragma once
#include "CPoint.h"
#include "Shape.h"

class CLineSegment : public Shape
{
public:
	CLineSegment(CPoint start, CPoint end);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	CPoint m_start;
	CPoint m_end;
};