#pragma once
#include <sstream>

void ExpandTemplateFromArgs(int argc, char* argv[]);

void ExpandTemplateFromStream(std::istream& input, std::ostream& output);