// Crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum class CryptType {
	crypt,
	decrypt
};

struct Args {
	CryptType cryptType;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

int KeyToInt(const std::string& str)
{
	const std::invalid_argument keyError("Invalid key argument\nKey must be number from 0 to 255\n");

	try {
		int key = std::stoi(str);
		if (key < 0 || key > 255)
		{
			throw keyError;
		}

		return key;
	}
	catch (const std::exception& ex) {
		throw keyError;
	}
}

CryptType ParseType(const std::string& str)
{
	if (str == "crypt")
	{
		return CryptType::crypt;
	}

	if (str == "decrypt")
	{
		return CryptType::decrypt;
	}

	throw std::invalid_argument("Invalid encryption type! The encryption type type must be 'crypt' or 'decrypt'");
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			"Invalid argument count.\n"
			"Usage: crypt.exe <encryption type> <input file> <output file> <key>\n"
			"The encryption type type must be 'crypt' or 'decrypt'\n"
		);
	}


	Args args;
	args.cryptType = ParseType(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = KeyToInt(argv[4]);

	return args;
}

unsigned char ShuffleByte(unsigned char byte,const std::vector<int>& bits)
{
	unsigned char shuffledByte = 0;

	for (int i = 0; i < 8; i++)
	{
		shuffledByte = shuffledByte | ((byte >> bits[i] & 1) << i);
	}

	return shuffledByte;
}

unsigned char CryptByte(unsigned char byte, int key)
{
	unsigned char xorByte = byte ^ key;
	std::vector<int> bits = { 5, 6, 0, 1, 2, 7, 3, 4 };

	return ShuffleByte(xorByte, bits);
}

unsigned char DecryptByte(unsigned char byte, int key)
{
	std::vector<int> bits = { 2, 3, 4, 6, 7, 0, 1, 5 };
	unsigned char shuffledByte = ShuffleByte(byte, bits);
	unsigned char xorByte = shuffledByte ^ key;

	return xorByte;
}

unsigned char EncryptionByte(unsigned char byte, const Args& args)
{
	switch (args.cryptType)
	{
	case (CryptType::crypt):
		return CryptByte(byte, args.key);
	case (CryptType::decrypt):
		return DecryptByte(byte, args.key);
	default:
		throw std::runtime_error("There is no handler for this type");
	}	
}

void FileEncryption(const Args& args)
{
	std::ifstream inputFile(args.inputFileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open input file " + args.inputFileName + "\n");
	}

	std::ofstream outputFile(args.outputFileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open output file " + args.inputFileName + "\n");
	}

	unsigned char byte;
	while (inputFile.get(reinterpret_cast<char&>(byte)))
	{
		unsigned char cryptedByte = EncryptionByte(byte, args);
		outputFile.put(reinterpret_cast<char&>(cryptedByte));
	}

}

int main(int argc, char* argv[])
{
	try {
		Args args = ParseArgs(argc, argv);
		FileEncryption(args);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';

		return 1;
	}

	return 0;
}