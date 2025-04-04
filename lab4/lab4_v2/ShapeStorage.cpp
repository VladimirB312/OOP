#include "ShapeStorage.h"


void ShapeStorage::AddShape(std::shared_ptr<IShape> shape)
{
	m_shapes.push_back(shape);
}

std::optional<std::shared_ptr<IShape>> ShapeStorage::GetMaxAreaShape()
{
	if (m_shapes.empty())
	{		
		return std::nullopt;
	}

	auto maxAreaShape = std::max_element(
		m_shapes.begin(), m_shapes.end(),
		[](std::shared_ptr<IShape>& a, std::shared_ptr<IShape>& b) {
			return a->GetArea() < b->GetArea();
		});

	return *maxAreaShape;
}

std::optional<std::shared_ptr<IShape>> ShapeStorage::GetMinPerimeterShape()
{
	if (m_shapes.empty())
	{
		return std::nullopt;
	}

	auto minPerimeterShape = std::min_element(
		m_shapes.begin(), m_shapes.end(),
		[](std::shared_ptr<IShape>& a, std::shared_ptr<IShape>& b) {
			return a->GetArea() < b->GetArea();
		});

	return *minPerimeterShape;
}