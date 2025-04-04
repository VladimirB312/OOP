#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <optional>

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	void SetOutlineColor(uint32_t color) override;
	void SetFillColor(uint32_t color) override;
	CPoint GetLeftTop();
	CPoint GetRightBottom();
	double GetWidth();
	double GetHeight();

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
	uint32_t m_outlineColor = 0x000000FF;
	uint32_t m_fillColor = 0xFFFFFFFF;
};