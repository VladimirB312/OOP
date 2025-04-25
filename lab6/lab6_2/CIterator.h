#pragma once
#include <stdexcept>

template <typename T, typename V>
class CIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = V;
	using element_type = V;
	using pointer = V*;
	using reference = V&;
	using difference_type = std::ptrdiff_t;

	CIterator(T node, T sentinel)
		: m_node(node)
		, m_sentinel(sentinel)
	{
	}

	CIterator(const CIterator& other)
		: CIterator(other.m_node, other.m_sentinel)
	{
	}

	template <std::convertible_to<T> CT, std::convertible_to<V> CV>
	explicit CIterator(const CIterator<CT, CV>& other)
		: m_node(other.m_node)
		, m_sentinel(other.m_sentinel)
	{
	}

	V& operator*()
	{
		if (m_node == m_sentinel)
		{
			throw std::logic_error("Ñannot be dereferenced");
		}
		return m_node->m_data;
	}

	CIterator& operator++()
	{
		m_node = m_node->m_next;
		return *this;
	}

	CIterator operator++(int)
	{
		auto copy = *this;
		++(*this);
		return copy;
	}

	CIterator& operator--()
	{
		m_node = m_node->m_prev;
		return *this;
	}

	CIterator operator--(int)
	{
		auto copy = *this;
		--(*this);
		return copy;
	}

	bool operator==(const CIterator& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(const CIterator& other) const
	{
		return m_node != other.m_node;
	}

private:
	friend class CStringList;
	T m_node = nullptr;
	T m_sentinel = nullptr;
};
