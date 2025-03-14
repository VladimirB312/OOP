#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace symbol_marker
{
const char WALL = '#';
const char START = 'A';
const char END = 'B';
const char EMPTY = ' ';
const char DOT = '.';
} // namespace symbol_marker

namespace digit_marker
{
const int WALL = -5;
const int START = -1;
const int END = -2;
const int DOT = -3;
const int EMPTY = 0;
} // namespace digit_marker

using Area = std::vector<std::vector<int>>;

const int MAX_AREA_SIZE = 100;

struct Point
{
	int x, y;
};

struct Labyrinth
{
	Point start, finish;
	Area area;
};

int MapPointToDigit(char ch)
{
	switch (ch)
	{
	case symbol_marker::WALL:
		return digit_marker::WALL;
	case symbol_marker::START:
		return digit_marker::START;
	case symbol_marker::END:
		return digit_marker::END;
	case symbol_marker::EMPTY:
		return digit_marker::EMPTY;
	default:
		throw std::runtime_error("ERROR");
	}
}

std::vector<int> GetLabyrinthLine(const std::string& line)
{
	std::vector<int> row;
	for (const auto ch : line)
	{
		if (row.size() >= MAX_AREA_SIZE)
		{
			throw std::runtime_error("ERROR");
		}

		row.push_back(MapPointToDigit(ch));
	}

	return row;
}

void SetStartAndFinishPoints(Labyrinth& labyrinth)
{
	int countA = 0;
	int countB = 0;

	for (int i = 0; i < labyrinth.area.size(); i++)
	{
		for (int j = 0; j < labyrinth.area[i].size(); j++)
		{
			if (labyrinth.area[i][j] == -1)
			{
				labyrinth.start = { i, j };
				labyrinth.area[i][j] = 0;
				countA++;
			}

			if (labyrinth.area[i][j] == -2)
			{
				labyrinth.finish = { i, j };
				labyrinth.area[i][j] = 0;
				countB++;
			}
		}
	}

	if (countA != 1 || countB != 1)
	{
		throw std::runtime_error("ERROR");
	}
}

Labyrinth ReadLabyrinthFromStream(std::istream& inputStream)
{
	Labyrinth labyrinth;

	std::string line;
	while (std::getline(inputStream, line))
	{
		if (labyrinth.area.size() >= MAX_AREA_SIZE)
		{
			throw std::runtime_error("ERROR");
		}

		labyrinth.area.push_back(GetLabyrinthLine(line));
	}

	SetStartAndFinishPoints(labyrinth);

	return labyrinth;
}

Labyrinth ReadLabyrinthFromFile(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file " + fileName + "\n");
	}

	return ReadLabyrinthFromStream(inputFile);
}

char DigitToMapPoint(int digit)
{
	switch (digit)
	{
	case digit_marker::WALL:
		return symbol_marker::WALL;
	case digit_marker::START:
		return symbol_marker::START;
	case digit_marker::END:
		return symbol_marker::END;
	case digit_marker::DOT:
		return symbol_marker::DOT;
	default:
		return symbol_marker::EMPTY;
	}
}

void PrintLabyrinthToStream(std::ostream& outputStream, Labyrinth& labyrinth)
{
	labyrinth.area[labyrinth.start.x][labyrinth.start.y] = -1;
	labyrinth.area[labyrinth.finish.x][labyrinth.finish.y] = -2;

	for (int i = 0; i < labyrinth.area.size(); i++)
	{
		for (int j = 0; j < labyrinth.area[i].size(); j++)
		{
			outputStream << DigitToMapPoint(labyrinth.area[i][j]);
		}
		if (i != labyrinth.area.size() - 1)
		{
			outputStream << '\n';
		}
	}
}

void PrintLabyrinthToFile(const std::string& fileName, Labyrinth& labyrinth)
{
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file " + fileName + "\n");
	}

	PrintLabyrinthToStream(outputFile, labyrinth);
}

bool IsEqual(Point point, int x, int y)
{
	return point.x == x && point.y == y;
}

void CheckOutOfRange(const Area& area, int x, int y)
{
	bool outMinRange = y < 0 || x < 0;
	bool outMaxRange = !(y < area.size() && x < area[y].size());

	if (outMinRange || outMaxRange)
	{
		throw std::runtime_error("Out of range!");
	}
}

bool ChoiceDirection(Labyrinth& labyrinth, std::queue<Point>& queue, Point& current, int shiftX, int shiftY)
{
	CheckOutOfRange(labyrinth.area, shiftY, shiftX);

	if (IsEqual(labyrinth.finish, shiftX, shiftY))
	{
		labyrinth.area[shiftX][shiftY] = labyrinth.area[current.x][current.y] + 1;
		return true;
	}

	if (labyrinth.area[shiftX][shiftY] == 0 && !(IsEqual(labyrinth.start, shiftX, shiftY)))
	{
		labyrinth.area[shiftX][shiftY] = labyrinth.area[current.x][current.y] + 1;
		queue.push({ shiftX, shiftY });
	}

	return false;
}

bool BaypassLabyrinth(Labyrinth& labyrinth, std::queue<Point>& queue)
{
	Point current = queue.front();
	queue.pop();

	if (ChoiceDirection(labyrinth, queue, current, current.x - 1, current.y))
	{
		return true;
	}
	if (ChoiceDirection(labyrinth, queue, current, current.x, current.y + 1))
	{
		return true;
	}
	if (ChoiceDirection(labyrinth, queue, current, current.x + 1, current.y))
	{
		return true;
	}
	if (ChoiceDirection(labyrinth, queue, current, current.x, current.y - 1))
	{
		return true;
	}

	return false;
}

bool FindPath(Labyrinth& labyrinth)
{
	std::queue<Point> queue;
	queue.push(labyrinth.start);

	while (!queue.empty())
	{
		if (BaypassLabyrinth(labyrinth, queue))
		{
			return true;
		}
	}

	return false;
}

bool ChoiceDirection(const Area& area, Point& current, int shiftX, int shiftY)
{
	if (area[shiftX][shiftY] + 1 == area[current.x][current.y])
	{
		current.x = shiftX;
		current.y = shiftY;
		return true;
	}

	return false;
}

Point GetPrevPoint(const Labyrinth& labyrinth, Point& current)
{
	if (ChoiceDirection(labyrinth.area, current, current.x, current.y - 1))
	{
		return current;
	}
	if (ChoiceDirection(labyrinth.area, current, current.x, current.y + 1))
	{
		return current;
	}
	if (ChoiceDirection(labyrinth.area, current, current.x - 1, current.y))
	{
		return current;
	}
	if (ChoiceDirection(labyrinth.area, current, current.x + 1, current.y))
	{
		return current;
	}

	throw std::runtime_error("Can't find a previous step");
}

bool IsEqualPoints(Point p1, Point p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

Labyrinth FillPathInLabyrinth(const Labyrinth& labyrinth)
{
	Point current = labyrinth.finish;
	Labyrinth resultLabyrinth = labyrinth;
	while (!IsEqualPoints(current, labyrinth.start))
	{
		current = GetPrevPoint(labyrinth, current);
		if (IsEqualPoints(current, labyrinth.start))
		{
			return resultLabyrinth;
		}

		resultLabyrinth.area[current.x][current.y] = digit_marker::DOT;
	}

	throw std::runtime_error("Can't find a way out");
}

void ProcessLabyrinthFromStdin()
{
	Labyrinth labyrinth;
	labyrinth = ReadLabyrinthFromStream(std::cin);

	if (!FindPath(labyrinth))
	{
		PrintLabyrinthToStream(std::cout, labyrinth);

		return;
	}

	labyrinth = FillPathInLabyrinth(labyrinth);
	PrintLabyrinthToStream(std::cout, labyrinth);
}

void ProcessLabyrinthFromFile(const std::string& inputFileName, const std::string& outputFileName)
{
	Labyrinth labyrinth;
	labyrinth = ReadLabyrinthFromFile(inputFileName);

	if (!FindPath(labyrinth))
	{
		PrintLabyrinthToFile(outputFileName, labyrinth);

		return;
	}

	labyrinth = FillPathInLabyrinth(labyrinth);
	PrintLabyrinthToFile(outputFileName, labyrinth);
}

int main(int argc, const char* argv[])
{
	try
	{
		if (argc == 1)
		{
			ProcessLabyrinthFromStdin();
			return 0;
		}

		if (argc == 3)
		{
			ProcessLabyrinthFromFile(argv[1], argv[2]);
			return 0;
		}

		throw std::invalid_argument("Invalid argument count.\n");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}

	return 0;
}