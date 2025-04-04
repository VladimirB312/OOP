#pragma once
#include <cmath>

struct CPoint
{
	double x;
	double y;
	double GetDistanceTo(CPoint point)
	{
		return std::hypot(x - point.x, y - point.y);
	}
};
