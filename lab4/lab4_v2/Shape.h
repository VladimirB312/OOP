#pragma once
#include <stdexcept>
#include <string>

class ShapeException : public std::runtime_error
{
public:
	explicit ShapeException(const std::string& message)
		: std::runtime_error(message) {};
};

class Shape
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