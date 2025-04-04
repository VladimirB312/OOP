#pragma once
#include "IShape.h"
#include <vector>
#include <memory>
#include <optional>

class ShapeStorage
{
public:
	void AddShape(std::shared_ptr<IShape> shape);
	std::optional<std::shared_ptr<IShape>> GetMaxAreaShape();
	std::optional<std::shared_ptr<IShape>> GetMinPerimeterShape();

private:
	std::vector<std::shared_ptr<IShape>> m_shapes{};
};