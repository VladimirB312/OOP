#include "ShapeReader.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "SolidShape.h"

namespace
{
CPoint ReadPoint(std::istream& input)
{
	double x, y;
	if (!(input >> x >> y))
	{
		throw ShapeReaderException("invalid point");
	}

	return CPoint{ x, y };
}

uint32_t ReadColor(std::istream& input)
{
	uint32_t color;
	if (!(input >> std::hex >> color) || color > 0xFFFFFF)
	{
		throw ShapeReaderException("invalid color");
	}

	return color;
}
} // namespace

ShapeReader::ShapeReader(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap(
		  { { "line", [this](std::istream& input) { return GetLineSegment(input); } },
			  { "triangle", [this](std::istream& input) { return GetTriangle(input); } },
			  { "rectangle", [this](std::istream& input) { return GetRectangle(input); } },
			  { "circle", [this](std::istream& input) { return GetCircle(input); } } })
{
}

std::unique_ptr<Shape> ShapeReader::GetShape(std::istream& input)
{
	std::string shape;
	input >> shape;
	if (auto it = m_actionMap.find(shape); it != m_actionMap.end())
	{
		return it->second(input);
	}

	throw ShapeReaderException("Unknown shape");
}

std::unique_ptr<Shape> ShapeReader::GetLineSegment(std::istream& input)
{
	CPoint p1 = ReadPoint(input);
	CPoint p2 = ReadPoint(input);
	uint32_t color = ReadColor(input);

	auto line = std::make_unique<CLineSegment>(p1, p2);
	line->SetOutlineColor(color);

	return line;
}

std::unique_ptr<Shape> ShapeReader::GetTriangle(std::istream& input)
{
	CPoint v1 = ReadPoint(input);
	CPoint v2 = ReadPoint(input);
	CPoint v3 = ReadPoint(input);
	uint32_t outColor = ReadColor(input);
	uint32_t fillColor = ReadColor(input);

	auto triangle = std::make_unique<CTriangle>(v1, v2, v3);
	triangle->SetOutlineColor(outColor);
	triangle->SetFillColor(fillColor);

	return triangle;
}

std::unique_ptr<Shape> ShapeReader::GetRectangle(std::istream& input)
{
	CPoint leftTop = ReadPoint(input);
	CPoint rightBottom = ReadPoint(input);
	uint32_t outColor = ReadColor(input);
	uint32_t fillColor = ReadColor(input);

	auto rect = std::make_unique<CRectangle>(leftTop, rightBottom);
	rect->SetOutlineColor(outColor);
	rect->SetFillColor(fillColor);

	return rect;
}

std::unique_ptr<Shape> ShapeReader::GetCircle(std::istream& input)
{
	CPoint center = ReadPoint(input);
	double radius;

	if (!(input >> radius))
	{
		throw ShapeReaderException("invalid radius");
	}

	uint32_t outColor = ReadColor(input);
	uint32_t fillColor = ReadColor(input);

	auto circle = std::make_unique<CCircle>(center, radius);
	circle->SetOutlineColor(outColor);
	circle->SetFillColor(fillColor);

	return circle;
}