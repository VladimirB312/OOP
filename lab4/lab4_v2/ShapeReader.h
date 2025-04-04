#pragma once
#include "IShape.h"
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
	std::shared_ptr<IShape> GetShape(std::istream& input);

private:
	using Handler = std::function<std::shared_ptr<IShape>(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
	
	std::shared_ptr<IShape> GetLineSegment(std::istream& input);
	std::shared_ptr<IShape> GetTriangle(std::istream& input);
	std::shared_ptr<IShape> GetRectangle(std::istream& input);
	std::shared_ptr<IShape> GetCircle(std::istream& input);
};