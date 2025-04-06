#include "DrawShapes.h"

void DrawShapes(const std::vector<std::unique_ptr<Shape>>& shapes)
{

	sf::RenderWindow window(sf::VideoMode({ 600, 400 }), "Canvas", sf::Style::Default);
	CCanvas canvas(window);
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		window.clear(sf::Color::White);
		for (const auto& shape : shapes)
		{
			shape->Draw(canvas);
		}
		window.display();
	}
}