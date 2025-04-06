#pragma once
#include "Shape.h"
#include "ShapeReader.h"

void AddShapes(std::istream& input, std::ostream& output, std::vector<std::unique_ptr<Shape>>& m_shapes, ShapeReader& reader);

const Shape* GetShapeWithMaxArea(const std::vector<std::unique_ptr<Shape>>& shapes);

const Shape* GetShapeWithMinPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes);

void PrintShapeInfo(std::ostream& output, const Shape* shape);