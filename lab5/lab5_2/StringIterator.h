#pragma once
#include <stdexcept>

template <typename T, typename V>
class StringIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = V;
	using element_type = V;
	using pointer = V*;
	using reference = V&;
	using difference_type = std::ptrdiff_t;

	StringIterator(T* string, size_t index)
		: m_string(string)
		, m_index(index)
	{
	}

	//StringIterator(const T* string, size_t index)
	//	: m_string(string)
	//	, m_index(index)
	//{
	//}

	StringIterator& operator++()
	{
		m_index++;
		return *this;
	}

	StringIterator& operator--()
	{
		m_index--;
		return *this;
	}

	StringIterator operator++(int)
	{
		StringIterator tmp = *this;
		++(*this);
		return tmp;
	}

	bool operator==(const StringIterator& other) const
	{
		return m_string == other.m_string && m_index == other.m_index;
	}

	bool operator!=(const StringIterator& other) const
	{
		return !(*this == other);
	}

	const V& operator*() const
	{
		CheckOutOfRange();

		return (*m_string)[m_index];
	}

	V& operator*()
	{
		CheckOutOfRange();

		return (*m_string)[m_index];
	}

	bool CheckOutOfRange()
	{
		if (m_index >= m_string->GetLength())
		{
			throw std::out_of_range("iterator out of range");
		}
	}

private:
	T* m_string;
	size_t m_index;
};