#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() = 0;
	virtual void SetFillColor(uint32_t color) = 0;
	virtual ~ISolidShape() = default;
};
