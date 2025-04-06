#pragma once
#include "SolidShape.h"
#include "CPoint.h"
#include <optional>

class CTriangle : public SolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	double m_area;
	double m_perimeter;
	void CalculateProperties();
};