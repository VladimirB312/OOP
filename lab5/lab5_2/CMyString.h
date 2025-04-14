#pragma once
#include <memory>
#include <stdexcept>
#include <string>

class CMyString
{
public:
	CMyString() noexcept;

	CMyString(const char* pString);

	CMyString(const char* pString, size_t length);

	CMyString(const CMyString& other);

	CMyString(CMyString&& other) noexcept;

	CMyString& operator=(CMyString&& other) noexcept;

	CMyString& operator=(const CMyString& other);

	CMyString(const std::string& stlString);

	~CMyString();

	size_t GetLength() const;

	const char* GetStringData() const;

	CMyString SubString(size_t start, size_t length) const;

	void Clear();

	size_t GetCapacity();

private:
	inline static char s_emptyString[] = { '\0' };
	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};