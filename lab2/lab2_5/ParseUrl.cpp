#include "ParseUrl.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
namespace ProtocolName
{
const std::string HTTP = "http";
const std::string HTTPS = "https";
const std::string FTP = "ftp";
} // namespace ProtocolName

namespace PortNumber
{
const std::string HTTP = "80";
const std::string HTTPS = "443";
const std::string FTP = "21";
} // namespace PortNumber

std::string strToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char ch) { return std::tolower(ch); });

	return str;
}

std::string GetPort(std::string protocol)
{
	protocol = strToLower(protocol);

	if (protocol == ProtocolName::HTTP)
	{
		return PortNumber::HTTP;
	}

	if (protocol == ProtocolName::HTTPS)
	{
		return PortNumber::HTTPS;
	}

	if (protocol == ProtocolName::FTP)
	{
		return PortNumber::FTP;
	}

	throw std::runtime_error("Unknown protocol");
}

Url MatchToUrl(const std::smatch& match)
{
	Url url;
	url.host = match[2].str();
	url.port = !match[3].str().empty() ? match[3].str() : GetPort(match[1].str());
	url.document = match[4].str();

	return url;
}

Url ParseUrl(const std::string& url)
{
	std::regex urlPattern(
		R"(^(https?|ftp):\/\/)"
		R"(([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?)"
		R"((?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9]))+))"
		R"((?::(6553[0-5]|)"
		R"(655[0-3][0-5]|)"
		R"(65[0-4]\d{2}|)"
		R"(6[0-4]\d{3}|)"
		R"([1-5]\d{4}|)"
		R"([1-9]\d{0,3}))?)"
		R"((?:\/(.*))?$)",
		std::regex::icase);

	std::smatch match;

	if (!std::regex_match(url, match, urlPattern))
	{
		throw std::runtime_error("Invalid url");
	}

	return MatchToUrl(match);
}

void PrintUrl(std::ostream& output, Url& url)
{
	output << "HOST: " << url.host << "\n";
	output << "PORT: " << url.port << "\n";
	output << "DOC: " << url.document << "\n";
}
