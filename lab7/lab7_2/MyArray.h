#pragma once
#include "ArrayIterator.h"
#include <algorithm>
#include <memory>
#include <utility>

template <typename T>
class MyArray
{
public:
	using Iterator = ArrayIterator<T>;
	using ConstIterator = ArrayIterator<const T>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	MyArray() = default;
	MyArray(const MyArray& other);
	MyArray(MyArray&& other) noexcept;
	MyArray& operator=(MyArray&& other) noexcept;
	MyArray& operator=(const MyArray& other);

	template <typename CT>
		requires std::convertible_to<CT, T>
	MyArray& operator=(const MyArray<CT>& other);

	~MyArray();
	void Clear();
	void Resize(size_t newSize);
	void Push(T value);
	size_t GetSize() const;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ReverseIterator rbegin();
	ReverseIterator rend();

private:
	T* m_items = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;

	T* Allocate(size_t size);
	void Deallocate(T* buffer) noexcept;
	void Swap(MyArray& other);
};

template <typename T>
MyArray<T>::MyArray(const MyArray& other)
{
	m_items = Allocate(other.m_capacity);
	try
	{
		std::uninitialized_copy_n(other.m_items, other.m_size, m_items);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
	}
	catch (...)
	{
		Clear();
		throw;
	}
}

template <typename T>
template <typename CT>
	requires std::convertible_to<CT, T>
MyArray<T>& MyArray<T>::operator=(const MyArray<CT>& other)
{
	MyArray<T> copy;
	try
	{
		for (auto item : other)
		{
			copy.Push(static_cast<T>(item));
		}
	}
	catch (...)
	{
		copy.Clear();
		throw;
	}
	Swap(copy);

	return *this;
}

template <typename T>
MyArray<T>::MyArray(MyArray&& other) noexcept
{
	Swap(other);
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(MyArray&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		Swap(other);
	}

	return *this;
}

template <typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray& other)
{
	if (this != &other)
	{
		MyArray copy(other);
		Swap(copy);
	}

	return *this;
}

template <typename T>
MyArray<T>::~MyArray()
{
	Clear();
}

template <typename T>
void MyArray<T>::Clear()
{
	if (!m_items)
	{
		return;
	}
	std::destroy(begin(), end()); // begin end вместо указателей
	Deallocate(m_items);
	m_items = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
T* MyArray<T>::Allocate(size_t size)
{
	return static_cast<T*>(operator new(size * sizeof(T)));
};

template <typename T>
void MyArray<T>::Deallocate(T* buffer) noexcept
{
	operator delete(buffer);
}

template <typename T>
void MyArray<T>::Swap(MyArray& other)
{
	std::swap(m_items, other.m_items);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T>
void MyArray<T>::Resize(size_t newSize)
{
	T* newItems = Allocate(newSize);
	try
	{
		auto end = std::uninitialized_copy_n(m_items, std::min(m_size, newSize), newItems); // обернуть в try catch
		while (end != newItems + newSize)
		{
			new (end++) T();
		}
	}
	catch (...)
	{
		std::destroy(newItems, newItems + newSize);
		Deallocate(newItems);
		throw;
	}

	Clear();
	m_items = newItems;
	m_size = newSize;
	m_capacity = newSize;
}

template <typename T>
void MyArray<T>::Push(T value)
{
	if (m_size < m_capacity)
	{
		new (m_items + m_size) T(std::move(value));
		m_size++;
		return;
	}

	size_t newCapacity = std::max(size_t(1), m_capacity * 2);
	size_t newSize = m_size + 1;
	T* newItems = Allocate(newCapacity);

	try {
		auto end = std::uninitialized_copy_n(m_items, m_size, newItems);
		new (end) T(std::move(value));
	}
	catch (...)
	{
		std::destroy(newItems, newItems + newSize);
		Deallocate(newItems);
		throw;
	}

	Clear();
	m_items = newItems;
	m_capacity = newCapacity;
	m_size = newSize;
}

template <typename T>
size_t MyArray<T>::GetSize() const
{
	return m_size;
}

template <typename T>
T& MyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Out of range!");
	}

	return m_items[index];
}

template <typename T>
const T& MyArray<T>::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Out of range!");
	}

	return m_items[index];
}

template <typename T>
typename MyArray<T>::Iterator MyArray<T>::begin()
{
	return { m_items };
}

template <typename T>
typename MyArray<T>::Iterator MyArray<T>::end()
{
	return { m_items + m_size };
}

template <typename T>
typename MyArray<T>::ConstIterator MyArray<T>::begin() const
{
	return { m_items };
}

template <typename T>
typename MyArray<T>::ConstIterator MyArray<T>::end() const
{
	return { m_items + m_size };
}

template <typename T>
typename MyArray<T>::ReverseIterator MyArray<T>::rbegin()
{
	return ReverseIterator(end());
}

template <typename T>
typename MyArray<T>::ReverseIterator MyArray<T>::rend()
{
	return ReverseIterator(begin());
}
