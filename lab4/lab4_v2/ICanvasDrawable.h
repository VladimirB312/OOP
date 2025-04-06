#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
};