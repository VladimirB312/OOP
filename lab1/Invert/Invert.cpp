// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <limits> 
#include <iomanip>
#include <sstream>

const int MATRIX_SIZE = 3;
using Matrix3x3 = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

Matrix3x3 ReadMatrixFromStdin()
{
	Matrix3x3 matrix{};

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		std::string line;
		if (!std::getline(std::cin, line))
		{
			throw std::runtime_error("Invalid matrix format\n");
		}
		std::stringstream ss(line);
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (ss.eof() || !(ss >> matrix[i][j]))
			{
				ss.clear();
				if (ss.peek() == '\t' || ss.peek() == EOF || ss.peek() == '\n') {
					throw std::runtime_error("Invalid matrix format\n");
				}
				throw std::runtime_error("Invalid matrix\n");
			}
		}
		if (!ss.eof()) {
			throw std::runtime_error("Invalid matrix format\n");
		}
	}

	return matrix;
}

double ReadValueFromFile(std::istream& inputFile)
{
	double value;

	if (!(inputFile >> value))
	{
		if (inputFile.eof())
		{
			throw std::runtime_error("Invalid matrix format\n");
		}
		throw std::runtime_error("Invalid matrix\n");
	}

	return value;
}

void CheckExtraValue(std::istream& inputFile)
{
	char extra;
	if (inputFile >> extra)
	{
		throw std::runtime_error("Invalid matrix format\n");
	}
}

Matrix3x3 ReadMatrixFromFile(const std::string& inputFileName)
{
	Matrix3x3 matrix{};
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open file \"" + inputFileName + "\"\n");
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i][j] = ReadValueFromFile(inputFile);
		}
	}

	CheckExtraValue(inputFile);

	return matrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

double GetDeterminant(const Matrix3x3& matrix)
{
	double determinant = 0;
	determinant += matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
	determinant -= matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	determinant += matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

	if (abs(determinant) < std::numeric_limits<double>::epsilon())
	{
		throw std::runtime_error("Non-invertible");
	}

	return determinant;
}

Matrix3x3 GetTransposedMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 transposedMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}

	return transposedMatrix;
}

Matrix3x3 GetMinorMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 minorMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			double firstLine = matrix[(i + 1) % 3][(j + 1) % 3] * matrix[(i + 2) % 3][(j + 2) % 3];
			double secondLine = matrix[(i + 2) % 3][(j + 1) % 3] * matrix[(i + 1) % 3][(j + 2) % 3];
			minorMatrix[i][j] = firstLine - secondLine;
		}
	}

	return minorMatrix;
}

Matrix3x3 MultiplayingMatrixByNumber(const Matrix3x3& matrix, double number)
{
	Matrix3x3 resultMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			resultMatrix[i][j] = matrix[i][j] * number;
		}
	}

	return resultMatrix;
}

Matrix3x3 GetInversedMatrix(const Matrix3x3& matrix)
{
	double determinant = GetDeterminant(matrix);
	Matrix3x3 minorMatrix = GetMinorMatrix(matrix);
	Matrix3x3 transposedMatrix = GetTransposedMatrix(minorMatrix);
	double coefficient = 1.0 / determinant;
	Matrix3x3 inversedMatrix = MultiplayingMatrixByNumber(transposedMatrix, coefficient);

	return inversedMatrix;
}

Matrix3x3 ReadMatrix(int argc, char* argv[])
{
	if (argc == 1)
	{
		return ReadMatrixFromStdin();
	}

	return ReadMatrixFromFile(argv[1]);
}

bool NeedHelp(int argc, const std::string& arg)
{
	return arg == "-h";
}

void ProcessArgs(int argc, char* argv[])
{
	const std::string usageMessage = "Usage: invert.exe <inputMatrixFile>, or run without parameters and enter values manually\n";
	if (argc == 2 && NeedHelp(argc, argv[1]))
	{
		std::cout << usageMessage;
		exit(0);
	}

	if (argc > 2)
	{
		throw std::invalid_argument("Invalid argument count.\n" + usageMessage);
	}
}

int main(int argc, char* argv[])
{
	try {
		ProcessArgs(argc, argv);
		Matrix3x3 originalMatrix = ReadMatrix(argc, argv);
		Matrix3x3 inversedMatrix = GetInversedMatrix(originalMatrix);
		PrintMatrix(inversedMatrix);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}