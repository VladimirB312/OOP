#include "ShapeStorage.h"


void ShapeStorage::AddShape(std::unique_ptr<Shape> shape)
{
	m_shapes.push_back(shape);
}

std::unique_ptr<Shape> ShapeStorage::GetMaxAreaShape()
{
	//if (m_shapes.empty())
	//{		
	//	return std::nullopt;
	//}

	auto maxAreaShape = std::max_element(
		m_shapes.begin(), m_shapes.end(),
		[](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
			return a->GetArea() < b->GetArea();
		});

	return std::move(*maxAreaShape);
}

std::optional<std::unique_ptr<Shape>> ShapeStorage::GetMinPerimeterShape()
{
	if (m_shapes.empty())
	{
		return std::nullopt;
	}

	auto minPerimeterShape = std::min_element(
		m_shapes.begin(), m_shapes.end(),
		[](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
			return a->GetArea() < b->GetArea();
		});

	return std::move(*minPerimeterShape);
}