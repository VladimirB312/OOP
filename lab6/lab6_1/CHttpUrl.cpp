#include "CHttpUrl.h"
#include "CUrlParsingError.h"

namespace
{
namespace protocol_name
{
const std::string HTTP = "http";
const std::string HTTPS = "https";
} // namespace protocol_name

namespace port_number
{
const unsigned short HTTP = 80;
const unsigned short HTTPS = 443;
} // namespace port_number

void StrToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char ch) { return std::tolower(ch); });
}

Protocol StringToProtocol(std::string protocol)
{
	StrToLower(protocol);

	if (protocol == protocol_name::HTTP)
	{
		return Protocol::HTTP;
	}

	return Protocol::HTTPS;
}

std::string ProtocolToString(Protocol protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return protocol_name::HTTP;
	}
	return protocol_name::HTTPS;
}

std::smatch ParseUrl(const std::string& url)
{
	std::regex URL_PATTERN(
		R"(^(https?):\/\/)"
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

	if (!std::regex_match(url, match, URL_PATTERN))
	{
		throw CUrlParsingError("Invalid url");
	}

	return match;
}

bool IsValidProtocol(const Protocol& protocol)
{
	return (static_cast<int>(protocol) >= 0 && static_cast<int>(protocol) <= 1);
}

bool IsValidDomain(const std::string& domain)
{
	if (domain.empty())
	{
		return false;
	}

	std::regex domainRegex(
		R"(^([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?)"
		R"((?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?)+)$)",
		std::regex::icase);

	return std::regex_match(domain, domainRegex);
}

unsigned short GetPortFromProtocol(std::string protocol)
{
	StrToLower(protocol);

	if (protocol == protocol_name::HTTP)
	{
		return port_number::HTTP;
	}

	return port_number::HTTPS;
}

unsigned short GetPortFromProtocol(Protocol protocol)
{
	if (!IsValidProtocol(protocol))
	{
		throw CUrlParsingError("Invalid protocol");
	}

	return GetPortFromProtocol(ProtocolToString(protocol));
}
} // namespace

CHttpUrl::CHttpUrl(std::string const& url)
{
	MatchToUrl(ParseUrl(url));
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetPortFromProtocol(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (!IsValidProtocol(protocol) || !IsValidDomain(domain))
	{
		throw CUrlParsingError("Invalid url");
	}

	m_domain = domain;
	m_protocol = protocol;
	m_document = !document.empty() && document[0] == '/' ? document : '/' + document;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port = m_port == GetPortFromProtocol(m_protocol) ? "" : ':' + std::to_string(m_port);

	return ProtocolToString(m_protocol) + "://" + m_domain + port + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::MatchToUrl(const std::smatch& match)
{
	m_protocol = StringToProtocol(match[1].str());
	m_domain = match[2].str();
	m_port = !match[3].str().empty() ? std::stoi(match[3].str()) : GetPortFromProtocol(match[1].str());
	m_document = '/' + match[4].str();
}