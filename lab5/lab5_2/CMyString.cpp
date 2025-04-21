#include "CMyString.h"
#include <algorithm>
#include <cassert>
#include <iterator>

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
		m_size = std::exchange(other.m_size, 0);
		m_capacity = std::exchange(other.m_capacity, 0);
		m_chars = std::exchange(other.m_chars, s_emptyString);
	}

	return *this;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString copy(other);
		std::swap(m_size, copy.m_size);
		std::swap(m_capacity, copy.m_capacity);
		std::swap(m_chars, copy.m_chars);
	}

	return *this;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.data())
{
}

CMyString::~CMyString()
{
	Clear();
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

CMyString CMyString::operator+(const CMyString& other) const
{
	CMyString newStr(m_chars, (m_size + other.m_size) * 2);
	auto end = std::uninitialized_copy_n(other.m_chars, other.m_size, newStr.m_chars + m_size);
	*end = '\0';
	newStr.m_size = m_size + other.m_size;
	newStr.m_capacity = newStr.m_size * 2;

	return newStr;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	(*this) = (*this) + other;

	return *this;
}

CMyString CMyString::operator+(const std::string& stlString) const
{

	return (*this) + CMyString(stlString);
}

CMyString CMyString::operator+(const char* pString) const
{
	return (*this) + CMyString(pString);
}

bool CMyString::operator==(const CMyString& other) const
{
	if (m_size != other.m_size)
	{
		return false;
	}

	return std::equal(m_chars, m_chars + m_size, other.m_chars);
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !((*this) == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	return std::lexicographical_compare(
		this->begin(), this->end(),
		other.begin(), other.end());
}

bool CMyString::operator>(const CMyString& other) const
{
	return (*this) != other && !(*this < other);
}

bool CMyString::operator>=(const CMyString& other) const
{
	return !(*this < other);
}

bool CMyString::operator<=(const CMyString& other) const
{
	return !(*this > other);
}

char& CMyString::operator[](size_t index)
{
	assert(index < m_size);
	return m_chars[index];
}

const char& CMyString::operator[](size_t index) const
{
	assert(index < m_size);
	return m_chars[index];
}

CMyString operator+(const std::string& stlString, const CMyString& str)
{

	return CMyString(stlString) + str;
}

CMyString operator+(const char* pString, const CMyString& str)
{
	return CMyString(pString) + str;
}

StringIterator<CMyString, char> CMyString::begin()
{
	return StringIterator<CMyString, char>(this, 0);
}

std::reverse_iterator<StringIterator<CMyString, char>> CMyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

std::reverse_iterator<StringIterator<CMyString, char>> CMyString::rend()
{
	return std::make_reverse_iterator(begin());
}

StringIterator<CMyString, char> CMyString::end()
{
	return StringIterator<CMyString, char>(this, m_size);
}

StringIterator<const CMyString, const char> CMyString::begin() const
{
	return StringIterator<const CMyString, const char>(this, 0);
}

StringIterator<const CMyString, const char> CMyString::end() const
{
	return StringIterator<const CMyString, const char>(this, m_size);
}

StringIterator<const CMyString, const char> CMyString::cbegin() const
{
	return StringIterator<const CMyString, const char>(this, 0);
}

StringIterator<const CMyString, const char> CMyString::cend() const
{
	return StringIterator<const CMyString, const char>(this, m_size);
}

std::reverse_iterator<StringIterator<const CMyString, const char>> CMyString::rbegin() const
{
	return std::reverse_iterator<StringIterator<const CMyString, const char>>(end());
}

std::reverse_iterator<StringIterator<const CMyString, const char>> CMyString::rend() const
{
	return std::reverse_iterator<StringIterator<const CMyString, const char>>(begin());
}

std::reverse_iterator<StringIterator<const CMyString, const char>> CMyString::crbegin() const
{
	return std::reverse_iterator<StringIterator<const CMyString, const char>>(end());
}

std::reverse_iterator<StringIterator<const CMyString, const char>> CMyString::crend() const
{
	return std::reverse_iterator<StringIterator<const CMyString, const char>>(begin());
}

std::ostream& operator<<(std::ostream& stream, const CMyString& str)
{
	return stream << str.GetStringData();
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	std::string result;
	stream >> result;
	str = std::move(CMyString(result));

	return stream;
}
