#include "CMyString.h"

namespace
{
char* Allocate(size_t size)
{
	return static_cast<char*>(operator new(size));
}
void Deallocate(char* buffer) noexcept
{
	operator delete(buffer);
};
} // namespace

CMyString::CMyString() noexcept
	: m_chars{ s_emptyString } {};

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString)){};

CMyString::CMyString(const char* pString, size_t length)
	: m_size{ length }
	, m_capacity{ m_size }
	, m_chars{ Allocate(m_capacity + 1) }
{
	auto end = std::uninitialized_copy_n(pString, m_size, m_chars);
	*end = '\0';
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_chars, other.m_size)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_size{ std::exchange(other.m_size, 0) }
	, m_capacity{ std::exchange(other.m_capacity, 0) }
	, m_chars{ std::exchange(other.m_chars, s_emptyString) }
{
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_chars, other.m_chars);
	}

	return *this;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_capacity && m_chars != s_emptyString)
		{
			std::uninitialized_copy_n(other.m_chars, other.m_size + 1, m_chars);
			m_size = other.m_size;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}
	}

	return *this;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.data())
{
}

CMyString::~CMyString()
{
	if (m_chars != s_emptyString)
	{
		Deallocate(m_chars);
	}
};

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length = SIZE_MAX) const
{
	if (start > m_size)
	{
		return CMyString();
	}

	return CMyString(m_chars + start, std::min(m_size - start, length));
}

void CMyString::Clear()
{
	if (m_chars == s_emptyString)
	{
		return;
	}

	Deallocate(m_chars);
	m_chars = s_emptyString;
	m_size = 0;
	m_capacity = 0;
}

size_t CMyString::GetCapacity()
{
	return m_capacity;
}
