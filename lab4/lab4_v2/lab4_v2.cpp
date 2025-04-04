#include "ShapeReader.h"
#include "ShapeStorage.h"
#include <iostream>

void AddShapes(ShapeStorage& storage, ShapeReader& reader)
{
	std::string line;
	while (getline(std::cin, line))
	{
		std::istringstream strm(line);
		try
		{
			storage.AddShape(reader.GetShape(strm));
		}
		catch (const ShapeReaderException& ex)
		{
			std::cout << ex.what() << "\n";
		}
		catch (...)
		{
			throw;
		}
	}
}

void PrintShapeInfo(ShapeStorage& storage)
{
	auto maxAreaShape = storage.GetMaxAreaShape();
	auto minPerimeterShape = storage.GetMinPerimeterShape();

	if (maxAreaShape)
	{
		std::cout << maxAreaShape.value()->ToString() << '\n';
	}

	if (minPerimeterShape)
	{
		std::cout << minPerimeterShape.value()->ToString() << '\n';
	}
}

int main()
{
	try
	{
		ShapeStorage shapeStorage;
		ShapeReader shapeReader(std::cin, std::cout);
		AddShapes(shapeStorage, shapeReader);
		PrintShapeInfo(shapeStorage);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}
	return 0;
}
