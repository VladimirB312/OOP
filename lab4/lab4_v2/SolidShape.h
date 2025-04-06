#pragma once
#include "Shape.h"

class SolidShape : public Shape
{
public:
	uint32_t GetFillColor();
	void SetFillColor(uint32_t color);

	virtual ~SolidShape() = default;

protected:
	std::string GetInfo() override;

private:
	uint32_t m_fillColor = 0xFFFFFFFF;
};
