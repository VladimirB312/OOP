#pragma once
#include "CPoint.h"
#include "SolidShape.h"
#include <optional>

class CRectangle : public SolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};