#include "CCanvas.h"
#include "Uint32ToRgb.h"

const int DEFAULT_THICKNESS = 2;

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::VertexArray line(sf::PrimitiveType::Lines, 2);
	line[0].position = sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y));
	line[1].position = sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y));

	RGBColor color = Uint32ToRGB(lineColor);
	line[0].color = sf::Color(color.r, color.g, color.b);
	line[1].color = sf::Color(color.r, color.g, color.b);

	m_window.draw(line);
}

void CCanvas::DrawPolygon(std::vector<CPoint> points, uint32_t lineColor, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	
	for (int p = 0; p < points.size(); p++)
	{
		polygon.setPoint(p, { static_cast<float>(points[p].x), static_cast<float>(points[p].y) });
	}

	RGBColor lColor = Uint32ToRGB(lineColor);
	RGBColor fColor = Uint32ToRGB(fillColor);
	polygon.setOutlineThickness(DEFAULT_THICKNESS);
	polygon.setOutlineColor(sf::Color(lColor.r, lColor.g, lColor.b));
	polygon.setFillColor(sf::Color(fColor.r, fColor.g, fColor.b));

	m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition({ static_cast<float>(center.x), static_cast<float>(center.y) });
	circle.setOutlineThickness(DEFAULT_THICKNESS);

	RGBColor lColor = Uint32ToRGB(lineColor);
	RGBColor fColor = Uint32ToRGB(fillColor);
	circle.setOutlineColor(sf::Color(lColor.r, lColor.g, lColor.b));
	circle.setFillColor(sf::Color(fColor.r, fColor.g, fColor.b));

	m_window.draw(circle);
}
