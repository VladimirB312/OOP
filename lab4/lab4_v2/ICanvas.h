#pragma once
#include "CPoint.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void DrawPolygon(std::vector<CPoint>, uint32_t lineColor, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor) = 0;
	virtual ~ICanvas() = default;
};