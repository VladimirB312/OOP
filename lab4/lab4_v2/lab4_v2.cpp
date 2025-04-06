#include "ShapeReader.h"
#include "ShapeUtils.h"
#include <iostream>
#include "DrawShapes.h"

int main()
{
	try
	{
		std::vector<std::unique_ptr<Shape>> shapes;
		ShapeReader shapeReader(std::cin, std::cout);
		AddShapes(std::cin, std::cout, shapes, shapeReader);

		std::cout << "Shape with max area:\n";
		PrintShapeInfo(std::cout, GetShapeWithMaxArea(shapes));

		std::cout << "Shape with min perimeter:\n";
		PrintShapeInfo(std::cout, GetShapeWithMinPerimeter(shapes));

		DrawShapes(shapes);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}
	return 0;
}
