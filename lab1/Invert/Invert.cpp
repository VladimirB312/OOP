// Invert.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <limits> 
#include <iomanip>

const int MATRIX_SIZE = 3;
using Matrix3x3 = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

Matrix3x3 ReadMatrixFromStdin()
{
	Matrix3x3 matrix{};
	std::cout << "Enter matrix values: \n";

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (std::cin.eof() || !(std::cin >> matrix[i][j]))
			{
				throw std::runtime_error("Invalid matrix\n");
			}
		}
	}

	return matrix;
}

void ReadValueFromFile(std::istream& inputFile, double& value)
{
	if (!(inputFile >> value))
	{
		if (inputFile.eof())
		{
			throw std::runtime_error("Invalid matrix format\n");
		}
		throw std::runtime_error("Invalid matrix\n");
	}
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
			ReadValueFromFile(inputFile, matrix[i][j]);
		}
	}

	CheckExtraValue(inputFile);

	return matrix;
}

void PrintMatrix(const Matrix3x3& m)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << std::setprecision(5) << m[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

double GetDeterminant(const Matrix3x3& m)
{
	double determinant = 0;
	determinant += m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
	determinant -= m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	determinant += m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

	if (abs(determinant) < std::numeric_limits<double>::epsilon())
	{
		throw std::runtime_error("Non-invertible");
	}

	return determinant;
}

Matrix3x3 GetTransposedMatrix(const Matrix3x3& m)
{
	Matrix3x3 transposedMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			transposedMatrix[j][i] = m[i][j];
		}
	}

	return transposedMatrix;
}

Matrix3x3 GetMinorMatrix(const Matrix3x3& m)
{
	Matrix3x3 minorMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			double firstLine = m[(i + 1) % 3][(j + 1) % 3] * m[(i + 2) % 3][(j + 2) % 3];
			double secondLine = m[(i + 2) % 3][(j + 1) % 3] * m[(i + 1) % 3][(j + 2) % 3];	
			minorMatrix[i][j] = firstLine - secondLine;
		}
	}

	return minorMatrix;
}

Matrix3x3 GetInverseMatrix(const Matrix3x3& m)
{
	double determinant = GetDeterminant(m);
	Matrix3x3 minorMatrix = GetMinorMatrix(m);
	Matrix3x3 transposedMatrix = GetTransposedMatrix(minorMatrix);

	Matrix3x3 inversedMatrix{};
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			inversedMatrix[i][j] = transposedMatrix[i][j] * (1.0 / determinant);
		}
	}

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
	Matrix3x3 originalMatrix{};

	try {
		ProcessArgs(argc, argv);
		originalMatrix = ReadMatrix(argc, argv);
		Matrix3x3 inverseMatrix = GetInverseMatrix(originalMatrix);
		PrintMatrix(inverseMatrix);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}