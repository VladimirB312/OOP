#pragma once
#include "CPoint.h"
#include "SolidShape.h"
#include <optional>

class CRectangle : public SolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	CPoint GetLeftTop();
	CPoint GetRightBottom();
	double GetWidth();
	double GetHeight();

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
	uint32_t m_fillColor = 0xFFFFFFFF;
};