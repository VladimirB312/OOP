#pragma once
#include <cassert>
#include <concepts>
#include <iterator>
#include <stdexcept>

template <typename T>
class ArrayIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using element_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = std::ptrdiff_t;

	ArrayIterator(T* item);

	template <std::convertible_to<T*> CT>
	ArrayIterator(const ArrayIterator<CT>& other);

	ArrayIterator(const ArrayIterator& other);

	ArrayIterator& operator++();
	ArrayIterator operator++(int);
	ArrayIterator& operator--();
	ArrayIterator operator--(int);
	bool operator==(const ArrayIterator& other) const;
	bool operator!=(const ArrayIterator& other) const;
	ArrayIterator operator+(difference_type shift) const;
	ArrayIterator& operator+=(difference_type shift);
	difference_type operator-(const ArrayIterator& other) const;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T& operator*();
	const T& operator*() const;

private:
	T* m_item;
};

template <typename T>
ArrayIterator<T>::ArrayIterator(T* item)
	: m_item(item)
{
}

template <typename T>
template <std::convertible_to<T*> CT>
ArrayIterator<T>::ArrayIterator(const ArrayIterator<CT>& other)
	: m_item(other.m_item)
{
}

template <typename T>
ArrayIterator<T>::ArrayIterator(const ArrayIterator& other)
	: m_item(other.m_item)
{
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator++()
{
	++m_item;
	return *this;
}

template <typename T>
ArrayIterator<T> ArrayIterator<T>::operator++(int)
{
	ArrayIterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator--()
{
	--m_item;
	return *this;
}

template <typename T>
ArrayIterator<T> ArrayIterator<T>::operator--(int)
{
	ArrayIterator tmp = *this;
	--(*this);
	return tmp;
}

template <typename T>
bool ArrayIterator<T>::operator==(const ArrayIterator& other) const
{
	return m_item == other.m_item;
}

template <typename T>
bool ArrayIterator<T>::operator!=(const ArrayIterator& other) const
{
	return !(*this == other);
}

template <typename T>
ArrayIterator<T> ArrayIterator<T>::operator+(difference_type shift) const
{
	ArrayIterator other(*this);
	other += shift;

	return other;
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator+=(difference_type shift)
{
	m_item += shift;

	return *this;
}

template <typename T>
typename ArrayIterator<T>::difference_type ArrayIterator<T>::operator-(const ArrayIterator& other) const
{
	return m_item - other.m_item;
}

template <typename T>
T& ArrayIterator<T>::operator[](size_t index)
{
	return (*m_item)[index];
}

template <typename T>
const T& ArrayIterator<T>::operator[](size_t index) const
{
	return (*m_item)[index];
}

template <typename T>
const T& ArrayIterator<T>::operator*() const
{
	return *m_item;
}

template <typename T>
T& ArrayIterator<T>::operator*()
{
	return *m_item;
}

template <typename T>
ArrayIterator<T> operator+(typename ArrayIterator<T>::difference_type shift, ArrayIterator<T>& it)
{
	return it + shift;
}