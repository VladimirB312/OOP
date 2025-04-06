#pragma once
#include <stdexcept>
#include <string>
#include "ICanvasDrawable.h"

class ShapeException : public std::runtime_error
{
public:
	explicit ShapeException(const std::string& message)
		: std::runtime_error(message) {};
};

class Shape: public ICanvasDrawable
{
public:
	uint32_t GetOutlineColor() const;
	void SetOutlineColor(uint32_t color);
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const;
	virtual ~Shape() = default;

private:
	uint32_t m_outlineColor = 0x000000FF;
};