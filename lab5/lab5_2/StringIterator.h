#pragma once
#include <cassert>
#include <concepts>
#include <iterator>
#include <stdexcept>

template <typename T, typename V>
class StringIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = V;
	using element_type = V;
	using pointer = V*;
	using reference = V&;
	using difference_type = std::ptrdiff_t;

	StringIterator(T* string, size_t index);

	template <std::convertible_to<T*> CT>
	StringIterator(const StringIterator<CT, V>& other);

	StringIterator(const StringIterator& other);

	StringIterator& operator++();
	StringIterator operator++(int);
	StringIterator& operator--();
	StringIterator operator--(int);
	bool operator==(const StringIterator& other) const;
	bool operator!=(const StringIterator& other) const;
	StringIterator operator+(int shift) const;
	StringIterator& operator+=(int shift);
	int operator-(const StringIterator& other) const;

	V& operator[](size_t index);
	const V& operator[](size_t index) const;	
	V& operator*();
	const V& operator*() const;

private:
	T* m_string;
	size_t m_index;
};

template <typename T, typename V>
StringIterator<T, V>::StringIterator(T* string, size_t index)
	: m_string(string)
	, m_index(index)
{
}

template <typename T, typename V>
template <std::convertible_to<T*> CT>
StringIterator<T, V>::StringIterator(const StringIterator<CT, V>& other)
	: m_string(other.m_string)
	, m_index(other.m_index)
{
}

template <typename T, typename V>
StringIterator<T, V>::StringIterator(const StringIterator& other)
	: m_string(other.m_string)
	, m_index(other.m_index)
{
}

template <typename T, typename V>
StringIterator<T, V>& StringIterator<T, V>::operator++()
{
	assert(m_index < m_string->GetLength());
	m_index++;
	return *this;
}

template <typename T, typename V>
StringIterator<T, V> StringIterator<T, V>::operator++(int)
{
	assert(m_index < m_string->GetLength());
	StringIterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename T, typename V>
StringIterator<T, V>& StringIterator<T, V>::operator--()
{
	assert(m_index > 0);
	m_index--;
	return *this;
}

template <typename T, typename V>
StringIterator<T, V> StringIterator<T, V>::operator--(int)
{
	assert(m_index > 0);
	StringIterator tmp = *this;
	--(*this);
	return tmp;
}

template <typename T, typename V>
bool StringIterator<T, V>::operator==(const StringIterator& other) const
{
	return m_string == other.m_string && m_index == other.m_index;
}

template <typename T, typename V>
bool StringIterator<T, V>::operator!=(const StringIterator& other) const
{
	return !(*this == other);
}

template <typename T, typename V>
StringIterator<T, V> StringIterator<T, V>::operator+(int shift) const
{
	StringIterator other(*this);
	other += shift;

	return other;
}

template <typename T, typename V>
StringIterator<T, V>& StringIterator<T, V>::operator+=(int shift)
{
	assert(m_index + shift < m_string->GetLength());
	m_index += shift;

	return *this;
}

template <typename T, typename V>
int StringIterator<T, V>::operator-(const StringIterator& other) const
{
	return static_cast<int>(m_index) - static_cast<int>(other.m_index);
}

template <typename T, typename V>
V& StringIterator<T, V>::operator[](size_t index)
{
	assert(index < m_string->GetLength());

	return (*m_string)[index];
}

template <typename T, typename V>
const V& StringIterator<T, V>::operator[](size_t index) const
{
	assert(index < m_string->GetLength());

	return (*m_string)[index];
}

template <typename T, typename V>
const V& StringIterator<T, V>::operator*() const
{
	assert(m_index < m_string->GetLength());

	return (*m_string)[m_index];
}

template <typename T, typename V>
V& StringIterator<T, V>::operator*()
{
	assert(m_index < m_string->GetLength());

	return (*m_string)[m_index];
}

template <typename T, typename V>
StringIterator<typename T, typename V> operator+(int shift, StringIterator<T, V>& it)
{
	return it + shift;
}