// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <fstream>
#include <string>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;
const int MATRIX_SIZE = 3;

Matrix3x3 ReadMatrixFromStdin(bool& wasError)
{
	Matrix3x3 matrix{};
	std::cout << "Enter matrix values: \n";

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (std::cin.eof())
			{
				wasError = true;
				std::cout << "ERROR\n";
				return matrix;
			}
			std::cout << "Matrix [" << i << "]" << "[" << j << "] = ";
			std::cin >> matrix[i][j];
		}
	}

	return matrix;
}

Matrix3x3 ReadMatrixFromFile(const std::string& inputFileName, bool& wasError)
{
	Matrix3x3 matrix{};
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		wasError = true;
		std::cout << "Failed to open file \"" << inputFileName << "\"\n";
		return matrix;
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (!(inputFile >> matrix[i][j]))
			{
				wasError = true;
				std::cout << "Failed to read matrix value from file \"" << inputFileName << "\"\n";
				return matrix;
			}
		}
	}

	return matrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	Matrix3x3 originalMatrix{};
	bool wasError = false;

	switch (argc)
	{
	case 1:
		originalMatrix = ReadMatrixFromStdin(wasError);
		break;
	case 2:
	{
		originalMatrix = ReadMatrixFromFile(argv[1], wasError);
		break;
	}
	default:
		return 1;
	}

	if (wasError)
	{
		return 1;
	}

	PrintMatrix(originalMatrix);

	return 0;
}
