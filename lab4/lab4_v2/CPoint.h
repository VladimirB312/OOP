#pragma once
#include <cmath>

struct CPoint
{
	double x;
	double y;
	double GetDistanceTo(CPoint point) const
	{
		return std::hypot(x - point.x, y - point.y);
	}
};
