#pragma once
#include "Dictionary.h"

std::string ParseWord(const std::string& line, size_t& pos);

std::vector<std::string> ParseTranslations(const std::string& line, size_t& pos);

void ParseEntrieFromString(const std::string& line, Entries& words);

Entries ParseEntriesFromFile(std::istream& inputFile);