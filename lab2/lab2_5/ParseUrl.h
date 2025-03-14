#pragma once
#include <string>

struct Url
{
	std::string host;
	std::string port;
	std::string document;
};

Url ParseUrl(const std::string& url);

void PrintUrl(std::ostream& output, Url& url);