#include <string>
#include <optional>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

std::optional<Args> GetParams(const int argc, char* argv[])
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
	if (searchString.size() == 0)
	{
		return subject;
	}

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

void CopyFileWithReplacement(const Args& args, bool& isCopySuccess)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(args.inputFileName);
	outputFile.open(args.outputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open input file: " << args.inputFileName << "\n";
		isCopySuccess = false;
		return;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open output file: " << args.outputFileName << "\n";
		isCopySuccess = false;
		return;
	}

	CopyStreamWithReplacement(inputFile, outputFile, args.searchString, args.replacementString);
	if (!outputFile.flush())
	{
		std::cout << "Failed to save data on disk\n";
		isCopySuccess = false;
	}
}

void ReplaceWordFromFile(const int argc, char* argv[], bool& isCopySuccess)
{
	const std::optional<Args> args = GetParams(argc, argv);

	if (!args)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		isCopySuccess = false;

		return;
	}

	CopyFileWithReplacement(args.value(), isCopySuccess);
}

std::string LinesToString()
{
	std::vector<std::string> inputStrings;
	std::string line;
	while (std::getline(std::cin, line))
	{
		inputStrings.push_back(line);
	}

	std::string allLines;
	for (const auto& str : inputStrings)
	{
		allLines.append(str).append("\n");
	}

	return allLines;
}

void ReplaceWordFromStdin()
{
	std::string searchString, replacementString;

	std::getline(std::cin, searchString);
	if (std::cin.eof())
	{
		std::cout << "ERROR\n";
		return;
	}

	std::getline(std::cin, replacementString);
	if (std::cin.eof())
	{
		std::cout << "ERROR\n";
		return;
	}

	std::istringstream inputStream(LinesToString());
	std::ostringstream outputStream;

	CopyStreamWithReplacement(inputStream, outputStream, searchString, replacementString);
	std::cout << outputStream.str();
}

int main(int argc, char* argv[])
{
	bool isCopySuccess = true;
	const std::string CALL_HELP_ARG = "-h";

	switch (argc)
	{
	case 1:
		ReplaceWordFromStdin();
		break;
	case 2:
	{
		if (argv[1] != CALL_HELP_ARG)
		{
			std::cout << "ERROR\n";
			return 1;
		}
		std::cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		break;
	}
	case 5:
		ReplaceWordFromFile(argc, argv, isCopySuccess);
		break;
	default:
		return 1;
	}

	if (!isCopySuccess)
	{
		return 1;
	}

	return 0;
}