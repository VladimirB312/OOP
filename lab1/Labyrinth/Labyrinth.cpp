// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <optional>
#include <iomanip>

using Area = std::vector<std::vector<int>>;

struct Point {
	int x, y;
};

struct Labyrinth {
	Point start, finish;
	Area area;
};

int MapPointToDigit(char ch)
{
	switch (ch)
	{
	case '#':
		return -5;
	case 'A':
		return -1;
	case 'B':
		return -2;
	case ' ':
		return 0;
	default:
		throw std::runtime_error("ERROR");
	}
}

std::vector<int> GetLabyrinthLine(const std::string& line)
{
	if (line.size() > 100)
	{
		throw std::runtime_error("ERROR");
	}
	std::vector<int> row;
	for (const auto ch : line)
	{
		row.push_back(MapPointToDigit(ch));

	}

	return row;
}

Point SetStartAndFinishPoints(Labyrinth& labyrinth)
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

	if (countA != 1 && countB != 1)
	{
		throw std::runtime_error("ERROR");
	}
}

Labyrinth ReadLabyrinthFromFile(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file " + fileName + "\n");
	}

	Labyrinth labyrinth;

	std::string line;
	while (std::getline(inputFile, line))
	{
		if (labyrinth.area.size() == 100)
		{
			throw std::runtime_error("ERROR");
		}

		labyrinth.area.push_back(GetLabyrinthLine(line));
	}

	SetStartAndFinishPoints(labyrinth);

	return labyrinth;
}

char DigitToMapPoint(int digit)
{
	switch (digit)
	{
	case -5:
		return '#';
	case -1:
		return 'A';
	case -2:
		return 'B';
	case -3:
		return '.';
	default:
		return ' ';
	}
}

void PrintLabyrinthToFile(const std::string& fileName, Labyrinth& labyrinth)
{
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Failed to open file " + fileName + "\n");
	}

	labyrinth.area[labyrinth.start.x][labyrinth.start.y] = -1;
	labyrinth.area[labyrinth.finish.x][labyrinth.finish.y] = -2;

	for (const auto& row : labyrinth.area)
	{
		for (const auto col : row)
		{
			outputFile << DigitToMapPoint(col);
		}
		outputFile << '\n';
	}
}

Labyrinth ReadLabyrinthFromStdin()
{
	Labyrinth labyrinth;
	return labyrinth;
}

bool IsEqual(Point point, int x, int y)
{
	return point.x == x && point.y == y;
}

bool CheckFinish(Labyrinth& labyrinth, std::queue<Point>& queue)
{
	Point current = queue.front();
	queue.pop();

	std::vector dx = { -1, 0, 1, 0 };
	std::vector dy = { 0, 1, 0, -1 };

	for (int i = 0; i < 4; i++)
	{
		int shiftX = current.x + dx[i];
		int shiftY = current.y + dy[i];

		if (IsEqual(labyrinth.finish, shiftX, shiftY))
		{
			labyrinth.area[shiftX][shiftY] = labyrinth.area[current.x][current.y] + 1;
			return true;
		}

		if (labyrinth.area[shiftX][shiftY] == 0 &&
			!(IsEqual(labyrinth.start, shiftX, shiftY)))
		{
			labyrinth.area[shiftX][shiftY] = labyrinth.area[current.x][current.y] + 1;
			queue.push({ shiftX , shiftY });
		}
	}

	return false;
}

bool FindPath(Labyrinth& labyrinth)
{
	std::queue<Point> queue;
	queue.push(labyrinth.start);

	while (!queue.empty())
	{
		if (CheckFinish(labyrinth, queue))
		{
			return true;
		}
	}

	return false;
}

Point GetPrevPoint(Labyrinth& labyrinth, Point& current)
{
	std::vector dx = { 0, 0, -1, 1 };
	std::vector dy = { -1, 1, 0, 0 };

	for (int i = 0; i < 4; i++)
	{
		int shiftX = current.x + dx[i];
		int shiftY = current.y + dy[i];

		if (labyrinth.area[shiftX][shiftY] + 1 == labyrinth.area[current.x][current.y])
		{
			current.x = shiftX;
			current.y = shiftY;
			return current;
		}
	}

	throw std::runtime_error("Can't find a previous step");
}

bool IsEqualPoints(Point p1, Point p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

Labyrinth FindWayBack(Labyrinth& labyrinth)
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

		resultLabyrinth.area[current.x][current.y] = -3;
	}

	throw std::runtime_error("Can't find a way out");
}

void ProcessLabyrinth(int argc, char* argv[])
{
	Labyrinth  labyrinth;

	if (argc == 1)
	{
		labyrinth = ReadLabyrinthFromStdin();
		return;
	}

	if (argc == 3)
	{
		labyrinth = ReadLabyrinthFromFile(argv[1]);
		if (!FindPath(labyrinth))
		{
			PrintLabyrinthToFile(argv[2], labyrinth);
			return;
		}
		labyrinth = FindWayBack(labyrinth);
		PrintLabyrinthToFile(argv[2], labyrinth);

		return;
	}

	throw std::invalid_argument("Invalid argument count.\n");
}

int main(int argc, char* argv[])
{
	try {
		ProcessLabyrinth(argc, argv);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
		return 1;
	}

	return 0;
}