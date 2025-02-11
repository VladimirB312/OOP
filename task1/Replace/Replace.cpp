#include "stdafx.h"
#include <string>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

std::optional<Args> getParams(const int argc, char* argv[])
{
	if (argc != 5)
	{
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replacementString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;

	while (pos < subject.size())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.size());
			break;
		}

		result.append(subject, pos, foundPos - pos).append(replacementString);
		pos = foundPos + searchString.size();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

void CopyFileWithReplacement(const std::optional<Args> args, bool& isCopySuccess)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(args->inputFileName);
	outputFile.open(args->outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input file: " << args->inputFileName << "\n";
		isCopySuccess = false;
		return;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file: " << args->outputFileName << "\n";
		isCopySuccess = false;
		return;
	}

	CopyStreamWithReplacement(inputFile, outputFile, args->searchString, args->replacementString);
	if (!outputFile.flush()) 
	{
		std::cout << "Failed to save data on disk\n";
		isCopySuccess = false;
	}
}

int main(int argc, char* argv[])
{
	const std::optional<Args> args = getParams(argc, argv);

	if (!args)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	bool isCopySuccess = true;
	CopyFileWithReplacement(args, isCopySuccess);

	if (!isCopySuccess)
	{
		std::cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}
