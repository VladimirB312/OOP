#pragma once
#include "Replacer.h"

struct Pattern {
	std::string key;
	std::string value;
};

std::string Trim(const std::string& str, char ch);

Pattern ParsePattern(const std::string& line);

void AddPattern(Patterns& patterns, const std::string& line);

Patterns GetPatternsFromStream(std::istream& input);

std::string GetReplacementString(std::istream& input);

Patterns GetPatternsFromArgs(int argc, char* argv[]);

void CheckFile(std::ifstream& file);

void CheckFile(std::ofstream& file);

void ExpandTemplateFromArgs(int argc, char* argv[]);

void ExpandTemplateFromStream(std::istream& input, std::ostream& output);