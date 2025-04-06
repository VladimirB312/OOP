#pragma once
#include "Shape.h"
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class ShapeReaderException : public std::runtime_error
{
public:
	explicit ShapeReaderException(const std::string& message)
		: std::runtime_error(message){};
};

class ShapeReader
{
public:
	ShapeReader(std::istream& input, std::ostream& output);
	std::unique_ptr<Shape> GetShape(std::istream& input);

private:
	using Handler = std::function<std::unique_ptr<Shape>(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
	
	std::unique_ptr<Shape> GetLineSegment(std::istream& input);
	std::unique_ptr<Shape> GetTriangle(std::istream& input);
	std::unique_ptr<Shape> GetRectangle(std::istream& input);
	std::unique_ptr<Shape> GetCircle(std::istream& input);
};