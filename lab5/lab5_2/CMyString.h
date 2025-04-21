#pragma once
#include "StringIterator.h"
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	CMyString() noexcept;
	explicit CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	explicit CMyString(const CMyString& other);
	CMyString(CMyString&& other) noexcept;
	explicit CMyString(const std::string& stlString);

	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator=(const CMyString& other);
	CMyString operator+(const CMyString& other) const;
	CMyString& operator+=(const CMyString& other);
	CMyString operator+(const std::string& stlString) const;
	CMyString operator+(const char* pString) const;
	bool operator==(const CMyString& other) const;
	bool operator!=(const CMyString& other) const;
	bool operator<(const CMyString& other) const;
	bool operator>(const CMyString& other) const;
	bool operator>=(const CMyString& other) const;
	bool operator<=(const CMyString& other) const;
	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	CMyString SubString(size_t start, size_t length) const;
	size_t GetCapacity();
	size_t GetLength() const;
	const char* GetStringData() const;
	void Clear();

	~CMyString();

	StringIterator<CMyString, char> begin();
	StringIterator<CMyString, char> end();
	StringIterator<const CMyString, const char> begin() const;
	StringIterator<const CMyString, const char> end() const;
	StringIterator<const CMyString, const char> cbegin() const;
	StringIterator<const CMyString, const char> cend() const;
	std::reverse_iterator<StringIterator<CMyString, char>> rbegin();
	std::reverse_iterator<StringIterator<CMyString, char>> rend();
	std::reverse_iterator<StringIterator<const CMyString, const char>> rbegin() const;
	std::reverse_iterator<StringIterator<const CMyString, const char>> rend() const;
	std::reverse_iterator<StringIterator<const CMyString, const char>> crbegin() const;
	std::reverse_iterator<StringIterator<const CMyString, const char>> crend() const;

private:
	inline static char s_emptyString[] = { '\0' };
	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};

CMyString operator+(const std::string& stlString, const CMyString& str);
CMyString operator+(const char* pString, const CMyString& str);
std::ostream& operator<<(std::ostream& stream, const CMyString& str);
std::istream& operator>>(std::istream& stream, CMyString& str);
