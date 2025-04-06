#pragma once
#include <cstdint>

struct RGBColor
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

RGBColor Uint32ToRGB(uint32_t color)
{
	return {
		static_cast<uint8_t>(color >> 16),
		static_cast<uint8_t>(color >> 8),
		static_cast<uint8_t>(color)
	};
}