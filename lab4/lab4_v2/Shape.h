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
	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString() = 0;
	uint32_t GetOutlineColor();
	void SetOutlineColor(uint32_t color);
	virtual ~Shape() = default;

protected:
	virtual std::string GetInfo();

private:
	uint32_t m_outlineColor = 0x000000FF;
};