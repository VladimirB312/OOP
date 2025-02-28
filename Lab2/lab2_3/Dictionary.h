#pragma once
#include <map>
#include <vector>
#include <string>

using Words = std::map<std::string, std::vector<std::string>>;

class Dictionary {
public:
	Dictionary();
	Dictionary(const std::string& fileName);	
	void Request(std::istream& input, std::ostream& output, const std::string& word);
	void Close();
//private:
	Words words;
	std::string fileName;
	bool isChanged = false;

	void ParseFile(std::ifstream& inputFile);
	void ParseWord(const std::string& line);
	std::string ParseKey(const std::string& line, size_t& pos);
	std::vector<std::string> ParseValues(const std::string& line, size_t& pos);	
	void PrintTranslations(std::ostream& output, const std::string& query);
	void AddWord(std::istream& input, const std::string& query);
	void SaveToFile();
};