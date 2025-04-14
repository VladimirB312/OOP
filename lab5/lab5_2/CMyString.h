#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>

class CMyString
{
public:
	CMyString() noexcept;
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(const CMyString& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(const std::string& stlString);

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
