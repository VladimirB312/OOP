#pragma once

template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less) noexcept
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = arr[0];
	for (auto const& el : arr)
	{
		if (less(maxValue, el))
		{
			maxValue = el;
		}
	}
	return true;
}