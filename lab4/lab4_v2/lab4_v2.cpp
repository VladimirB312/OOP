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
		std::cout << "Max area shape: ";
		std::cout << maxAreaShape.value()->ToString() << '\n';
	}

	if (minPerimeterShape)
	{
		std::cout << "Min perimeter shape: ";
		std::cout << minPerimeterShape.value()->ToString() << '\n';
	}
}


//class Man
//{
//public:
//	virtual int GetAge() const noexcept = 0;
//
//	virtual ~Man() = default;
//};
//
//class Worker : public Man
//{
//public:
//	Worker(std::string name)
//		: m_name{ std::move(name) }
//	{
//	}
//
//	int GetAge() const noexcept
//	{
//		return 42;
//	}
//
//private:
//	std::string m_name;
//};
//
//std::unique_ptr<Man> GetMan()
//{
//	return std::make_unique<Worker>("david");
//}
//
//void ShowMansAge(const Man& man)
//{
//	std::cout << man.GetAge() << std::endl;
//}


int main()
{

	//auto man = GetMan();
	//ShowMansAge(*man);

	//std::vector<std::unique_ptr<Man>> mens;
	//std::unique_ptr<Worker> worker;
	//mens.push_back(std::move(worker));

	/*try
	{
		ShapeStorage shapeStorage;
		ShapeReader shapeReader(std::cin, std::cout);
		AddShapes(shapeStorage, shapeReader);
		PrintShapeInfo(shapeStorage);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}*/
	return 0;
}
