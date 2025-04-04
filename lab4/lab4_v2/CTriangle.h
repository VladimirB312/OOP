#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <optional>

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	void SetOutlineColor(uint32_t color) override;	
	void SetFillColor(uint32_t color) override;
	CPoint GetVertex1();
	CPoint GetVertex2();
	CPoint GetVertex3();

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::optional<double> m_area;
	std::optional<double> m_perimeter;
	uint32_t m_outlineColor = 0x000000FF;
	uint32_t m_fillColor = 0xFFFFFFFF;
	void CalculateProperties();
};