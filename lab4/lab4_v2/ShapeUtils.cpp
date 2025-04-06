#include "ShapeUtils.h"

const Shape* GetShapeWithMaxArea(const std::vector<std::unique_ptr<Shape>>& shapes)
{
	if (shapes.empty())
	{
		return nullptr;
	}

	auto maxAreaShape = std::max_element(
		shapes.begin(), shapes.end(),
		[](const std::unique_ptr<Shape>& a, const std::unique_ptr<Shape>& b) {
			return a->GetArea() < b->GetArea();
		});

	return maxAreaShape != shapes.end() ? maxAreaShape->get() : nullptr;
}

const Shape* GetShapeWithMinPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes)
{
	if (shapes.empty())
	{
		return nullptr;
	}

	auto minPerimeterShape = std::min_element(
		shapes.begin(), shapes.end(),
		[](const std::unique_ptr<Shape>& a, const std::unique_ptr<Shape>& b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return minPerimeterShape != shapes.end() ? minPerimeterShape->get() : nullptr;
}

void AddShapes(std::istream& input, std::ostream& output, std::vector<std::unique_ptr<Shape>>& shapes, ShapeReader& reader)
{
	std::string line;
	while (getline(input, line))
	{
		std::istringstream strm(line);
		try
		{
			shapes.push_back(reader.GetShape(strm));
		}
		catch (const ShapeReaderException& ex)
		{
			output << ex.what() << "\n";
		}
		catch (...)
		{
			throw;
		}
	}
}

void PrintShapeInfo(std::ostream& output, const Shape* shape)
{
	if (!shape)
	{
		output << "shape doesn't exist\n";
		return;
	}

	output << shape->ToString();
}