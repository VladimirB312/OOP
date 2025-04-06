#pragma once
#include "CPoint.h"
#include "Shape.h"

class CLineSegment : public Shape
{
public:
	CLineSegment(CPoint start, CPoint end);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_start;
	CPoint m_end;
};