#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <optional>

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	void SetOutlineColor(uint32_t color) override;
	void SetFillColor(uint32_t color) override;
	CPoint GetCenter();
	double GetRadius();

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor = 0x000000FF;
	uint32_t m_fillColor = 0xFFFFFFFF;
};