// Labyrinth.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

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
	bool foundA = false;
	bool foundB = false;

	for (int i = 0; i < labyrinth.area.size(); i ++)
	{
		for (int j = 0; j < labyrinth.area[i].size(); j ++)
		{
			if (labyrinth.area[i][j] == -1)
			{
				labyrinth.start = { i, j };
				labyrinth.area[i][j] = 0;
				foundA = true;
			}

			if (labyrinth.area[i][j] == -2)
			{
				labyrinth.finish = { i, j };
				labyrinth.area[i][j] = 0;
				foundB = true;
			}
		}
	}

	if (!foundA || !foundB)
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