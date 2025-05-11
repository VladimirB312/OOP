#pragma once
#include <concepts>

template <typename T, typename Less>
	requires requires(Less l, T t) {
		{ l(t, t) } noexcept;
	}
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less) noexcept
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = arr[0];
	for (auto const& el : arr)
	{
		if (less(maxValue, el)) // less может кидать исключения
		{
			maxValue = el;
		}
	}
	return true;
}