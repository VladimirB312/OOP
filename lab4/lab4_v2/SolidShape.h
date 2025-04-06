#pragma once
#include "Shape.h"

class SolidShape : public Shape
{
public:
	uint32_t GetFillColor() const;
	void SetFillColor(uint32_t color);
	virtual std::string ToString() const override;
	virtual ~SolidShape() = default;	

private:
	uint32_t m_fillColor = 0xFFFFFFFF;
};
