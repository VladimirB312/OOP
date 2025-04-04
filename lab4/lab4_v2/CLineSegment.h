#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint start, CPoint end);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	void SetOutlineColor(uint32_t color) override;
	CPoint GetStartPoint();
	CPoint GetEndPoint();

private:
	CPoint m_start;
	CPoint m_end;
	uint32_t m_outlineColor = 0x000000FF;
};