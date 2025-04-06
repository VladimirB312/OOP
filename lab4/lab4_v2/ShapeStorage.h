#pragma once
#include "Shape.h"
#include <vector>
#include <memory>
#include <optional>

class ShapeStorage
{
public:
	void AddShape(std::unique_ptr<Shape> shape);
	std::unique_ptr<Shape> GetMaxAreaShape();
	std::optional<std::unique_ptr<Shape>> GetMinPerimeterShape();

private:
	std::vector<std::unique_ptr<Shape>> m_shapes{};
};