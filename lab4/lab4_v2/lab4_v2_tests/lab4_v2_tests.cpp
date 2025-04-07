#define CATCH_CONFIG_MAIN
// #include "../../../catch2/catch.hpp"
#include "../CCircle.h"
#include "../CLineSegment.h"
#include "../CPoint.h"
#include "../CRectangle.h"
#include "../CTriangle.h"
#include "../ShapeUtils.h"
#include "catch.hpp"
#include "fakeit.hpp"

SCENARIO("create line segment")
{
	WHEN("create line with points { 0, 0 }, { 0, 5 ")
	{
		CLineSegment line({ 0, 0 }, { 0, 5 });
		THEN("points of the line should be the same, area should be 5, perimetr 12 and outline color black")
		{
			CHECK(line.GetStartPoint().x == 0);
			CHECK(line.GetStartPoint().y == 0);
			CHECK(line.GetEndPoint().x == 0);
			CHECK(line.GetEndPoint().y == 5);
			CHECK(line.GetArea() == 5);
			CHECK(line.GetPerimeter() == 12);
			CHECK(line.GetOutlineColor() == 0x000000FF);
		}
		AND_WHEN("set outline color to white")
		{
			line.SetOutlineColor(0xFFFFFFFF);
			THEN("outline color will be white")
			{
				CHECK(line.GetOutlineColor() == 0xFFFFFFFF);
			}
		}
	}

	WHEN("create line with points { 3, 2 }, { 4, 17 }")
	{
		CLineSegment line({ 3, 2 }, { 4, 17 });
		THEN("area should be 15.033, perimetr 32.066")
		{
			CHECK_THAT(line.GetArea(), Catch::Matchers::WithinAbs(15.033, 0.001));
			CHECK_THAT(line.GetPerimeter(), Catch::Matchers::WithinAbs(32.066, 0.001));
		}
	}
}

SCENARIO("create triangle")
{
	WHEN("create triangle with points { 0, 0 }, { 4, 0 }, { 0, 4 } ")
	{
		CTriangle triangle({ 0, 0 }, { 4, 0 }, { 0, 4 });
		THEN("points of the triangle should be the same, area should be 8, perimeter 13.656 and outline color black")
		{
			CHECK(triangle.GetVertex1().x == 0);
			CHECK(triangle.GetVertex1().y == 0);
			CHECK(triangle.GetVertex2().x == 4);
			CHECK(triangle.GetVertex2().y == 0);
			CHECK(triangle.GetVertex3().x == 0);
			CHECK(triangle.GetVertex3().y == 4);
			CHECK_THAT(triangle.GetArea(), Catch::Matchers::WithinAbs(8.0, 0.001));
			CHECK_THAT(triangle.GetPerimeter(), Catch::Matchers::WithinAbs(13.656, 0.001));
			CHECK(triangle.GetOutlineColor() == 0x000000FF);
			CHECK(triangle.GetFillColor() == 0xFFFFFFFF);
		}

		AND_WHEN("set outline color to white")
		{
			triangle.SetOutlineColor(0xFFFFFFFF);
			THEN("outline color will be white")
			{
				CHECK(triangle.GetOutlineColor() == 0xFFFFFFFF);
			}
		}

		AND_WHEN("set fill color to black")
		{
			triangle.SetFillColor(0x000000FF);
			THEN("outline color will be black")
			{
				CHECK(triangle.GetOutlineColor() == 0x000000FF);
			}
		}
	}

	WHEN("create triangle with points { 1, 3 }, { 18, 6 }, { 8, 15 } ")
	{
		CTriangle triangle({ 1, 3 }, { 18, 6 }, { 8, 15 });
		THEN("area should be 91.5, perimeter 44.608 and outline color black")
		{
			CHECK_THAT(triangle.GetArea(), Catch::Matchers::WithinAbs(91.5, 0.001));
			CHECK_THAT(triangle.GetPerimeter(), Catch::Matchers::WithinAbs(44.608, 0.001));
		}
	}

	WHEN("create invalid triangle with points { 1, 3 }, { 5, 3 }, { 7, 3 } ")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CTriangle({ 1, 3 }, { 5, 3 }, { 7, 3 }), ShapeException);
		}
	}
}

SCENARIO("create rectangle")
{
	WHEN("create rectangle with left top point { 0, 0 } and right bottom point { 6, 4 } ")
	{
		CRectangle rect({ 0, 0 }, { 6, 4 });
		THEN("points of the triangle should be the same, area should be 24, perimeter 20 and outline color black")
		{
			CHECK(rect.GetLeftTop().x == 0);
			CHECK(rect.GetLeftTop().y == 0);
			CHECK(rect.GetRightBottom().x == 6);
			CHECK(rect.GetRightBottom().y == 4);
			CHECK_THAT(rect.GetArea(), Catch::Matchers::WithinAbs(24, 0.001));
			CHECK_THAT(rect.GetPerimeter(), Catch::Matchers::WithinAbs(20, 0.001));
			CHECK_THAT(rect.GetWidth(), Catch::Matchers::WithinAbs(6, 0.001));
			CHECK_THAT(rect.GetHeight(), Catch::Matchers::WithinAbs(4, 0.001));
			CHECK(rect.GetOutlineColor() == 0x000000FF);
			CHECK(rect.GetFillColor() == 0xFFFFFFFF);
		}

		AND_WHEN("set outline color to white")
		{
			rect.SetOutlineColor(0xFFFFFFFF);
			THEN("outline color will be white")
			{
				CHECK(rect.GetOutlineColor() == 0xFFFFFFFF);
			}
		}

		AND_WHEN("set fill color to black")
		{
			rect.SetFillColor(0x000000FF);
			THEN("outline color will be black")
			{
				CHECK(rect.GetOutlineColor() == 0x000000FF);
			}
		}
	}

	WHEN("create rectangle with left top point { 4, 8 } and right bottom point { 15, 27 } ")
	{
		CRectangle rect({ 4, 8 }, { 15, 27 });
		THEN("area should be 209, perimeter 60, width 11, height 19")
		{
			CHECK_THAT(rect.GetArea(), Catch::Matchers::WithinAbs(209, 0.001));
			CHECK_THAT(rect.GetPerimeter(), Catch::Matchers::WithinAbs(60, 0.001));
			CHECK_THAT(rect.GetWidth(), Catch::Matchers::WithinAbs(11, 0.001));
			CHECK_THAT(rect.GetHeight(), Catch::Matchers::WithinAbs(19, 0.001));
		}
	}

	WHEN("create rectangle with left top point { 1, 1 } and right bottom point { 1, 1 } ")
	{
		CRectangle rect({ 1, 1 }, { 1, 1 });
		THEN("all params should be 0")
		{
			CHECK_THAT(rect.GetArea(), Catch::Matchers::WithinAbs(0, 0.001));
			CHECK_THAT(rect.GetPerimeter(), Catch::Matchers::WithinAbs(0, 0.001));
			CHECK_THAT(rect.GetWidth(), Catch::Matchers::WithinAbs(0, 0.001));
			CHECK_THAT(rect.GetHeight(), Catch::Matchers::WithinAbs(0, 0.001));
		}
	}
}

SCENARIO("create circle")
{
	WHEN("create circle with center point { 20, 20 } and radius 10 ")
	{
		CCircle circle({ 20, 20 }, 10);
		THEN("points of the circle center and radius should be the same, should be 5, perimetr 12 and outline color black")
		{
			CHECK(circle.GetCenter().x == 20);
			CHECK(circle.GetCenter().y == 20);
			CHECK(circle.GetRadius() == 10);
			CHECK_THAT(circle.GetArea(), Catch::Matchers::WithinAbs(314.159, 0.001));
			CHECK_THAT(circle.GetPerimeter(), Catch::Matchers::WithinAbs(62.831, 0.001));
			CHECK(circle.GetOutlineColor() == 0x000000FF);
			CHECK(circle.GetFillColor() == 0xFFFFFFFF);
		}

		AND_WHEN("set outline color to white")
		{
			circle.SetOutlineColor(0xFFFFFFFF);
			THEN("outline color will be white")
			{
				CHECK(circle.GetOutlineColor() == 0xFFFFFFFF);
			}
		}

		AND_WHEN("set fill color to black")
		{
			circle.SetFillColor(0x000000FF);
			THEN("outline color will be black")
			{
				CHECK(circle.GetOutlineColor() == 0x000000FF);
			}
		}
	}

	WHEN("create circle with center point { 4, 8 } and radius 13 ")
	{
		CCircle circle({ 4, 8 }, 13);
		THEN("area should be 530.929, perimetr 12")
		{
			CHECK_THAT(circle.GetArea(), Catch::Matchers::WithinAbs(530.929, 0.001));
			CHECK_THAT(circle.GetPerimeter(), Catch::Matchers::WithinAbs(81.681, 0.001));
		}
	}

	WHEN("create invalid circle with center point { 4, 8 } and radius 0 ")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CCircle({ 4, 8 }, 0), ShapeException);
		}
	}

	WHEN("create invalid circle with center point { 4, 8 } and radius -1 ")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CCircle({ 4, 8 }, -1), ShapeException);
		}
	}
}

SCENARIO("get max area and min perimeter")
{
	GIVEN("shape storage with several shapes, where the circle with maximum area and the line with minimum perimeter")
	{
		std::vector<std::unique_ptr<Shape>> shapes;
		auto line = std::make_unique<CLineSegment>(CPoint{ 1, 3 }, CPoint{ 3, 5 });
		auto triangle = std::make_unique<CTriangle>(CPoint{ 1, 2 }, CPoint{ 7, 2 }, CPoint{ 3, 8 });
		auto rect = std::make_unique<CRectangle>(CPoint{ 0, 0 }, CPoint{ 15, 15 });
		auto circle = std::make_unique<CCircle>(CPoint{ 10, 10 }, 15);
		shapes.push_back(std::move(line));
		shapes.push_back(std::move(triangle));
		shapes.push_back(std::move(rect));
		shapes.push_back(std::move(circle));

		WHEN("get shape with a maximum area")
		{
			auto shape = GetShapeWithMaxArea(shapes);
			THEN("shape must be a circle with area 706.858")
			{
				std::istringstream strm(shape->ToString());
				std::string shapeName;
				strm >> shapeName;
				CHECK(shapeName == "Circle");
				CHECK_THAT(shape->GetArea(), Catch::Matchers::WithinAbs(706.858, 0.001));
			}
		}

		WHEN("get shape with a minimum perimeter")
		{
			auto shape = GetShapeWithMinPerimeter(shapes);
			THEN("shape must be a line with perimeter 7.656")
			{
				std::istringstream strm(shape->ToString());
				std::string shapeName;
				strm >> shapeName;
				CHECK(shapeName == "Line");
				CHECK_THAT(shape->GetPerimeter(), Catch::Matchers::WithinAbs(7.656, 0.001));
			}
		}
	}

	GIVEN("shape storage with several shapes, where the rectangle with maximum area and the triangle with minimum perimeter")
	{
		std::vector<std::unique_ptr<Shape>> shapes;
		auto line = std::make_unique<CLineSegment>(CPoint{ 2, 2 }, CPoint{ 100, 9 });
		auto triangle = std::make_unique<CTriangle>(CPoint{ 4, 3 }, CPoint{ 10, 4 }, CPoint{ 5, 10 });
		auto rect = std::make_unique<CRectangle>(CPoint{ 10, 10 }, CPoint{ 30, 30 });
		auto circle = std::make_unique<CCircle>(CPoint{ 2, 2 }, 4);
		shapes.push_back(std::move(line));
		shapes.push_back(std::move(triangle));
		shapes.push_back(std::move(rect));
		shapes.push_back(std::move(circle));

		WHEN("get shape with a maximum area")
		{
			auto shape = GetShapeWithMaxArea(shapes);
			THEN("shape must be a circle with area 400")
			{
				std::istringstream strm(shape->ToString());
				std::string shapeName;
				strm >> shapeName;
				CHECK(shapeName == "Rectangle");
				CHECK_THAT(shape->GetArea(), Catch::Matchers::WithinAbs(400, 0.001));
			}
		}

		WHEN("get shape with a minimum perimeter")
		{
			auto shape = GetShapeWithMinPerimeter(shapes);
			THEN("shape must be a triangle with perimeter 20.964")
			{
				std::istringstream strm(shape->ToString());
				std::string shapeName;
				strm >> shapeName;
				CHECK(shapeName == "Triangle");
				CHECK_THAT(shape->GetPerimeter(), Catch::Matchers::WithinAbs(20.964, 0.001));
			}
		}
	}
}

SCENARIO("draw shapes")
{
	fakeit::Mock<ICanvas> mockCanvas;
	WHEN("draw rectangle")
	{
		CRectangle rect({ 10, 30 }, { 40, 10 });
		CPoint leftBottom = { 10, 10 };
		CPoint rightBottom = { 40, 10 };
		CPoint rightTop = { 40, 30 };
		CPoint leftTop = { 10, 30 };
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;
		rect.SetFillColor(fillColor);
		rect.SetOutlineColor(outlineColor);

		THEN("rectangle should call the DrawPolygon method with the correct parameters")
		{
			fakeit::When(Method(mockCanvas, DrawPolygon)).Return();
			rect.Draw(mockCanvas.get());

			fakeit::Verify(Method(mockCanvas, DrawPolygon).Matching([&](std::vector<CPoint> points, uint32_t lColor, uint32_t fColor) {
				if (points.size() != 4)
				{
					return false;
				}
				if (points[0].x != leftBottom.x || points[0].y != leftBottom.y)
				{
					return false;
				}
				if (points[1].x != rightBottom.x || points[1].y != rightBottom.y)
				{
					return false;
				}
				if (points[2].x != rightTop.x || points[2].y != rightTop.y)
				{
					return false;
				}
				if (points[3].x != leftTop.x || points[3].y != leftTop.y)
				{
					return false;
				}
				if (lColor != outlineColor || fColor != fillColor)
				{
					return false;
				}
				return true;
			})).Exactly(fakeit::Once);
		}
	}

	WHEN("draw triangle")
	{
		CPoint vertex1 = { 10, 10 };
		CPoint vertex2 = { 40, 10 };
		CPoint vertex3 = { 20, 30 };
		CTriangle triangle(vertex1, vertex2, vertex3);
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;
		triangle.SetFillColor(fillColor);
		triangle.SetOutlineColor(outlineColor);

		THEN("triangle should call the DrawPolygon method with the correct parameters")
		{
			fakeit::When(Method(mockCanvas, DrawPolygon)).Return();
			triangle.Draw(mockCanvas.get());

			fakeit::Verify(Method(mockCanvas, DrawPolygon).Matching([&](std::vector<CPoint> points, uint32_t lColor, uint32_t fColor) {
				if (points.size() != 3)
				{
					return false;
				}
				if (points[0].x != vertex1.x || points[0].y != vertex1.y)
				{
					return false;
				}
				if (points[1].x != vertex2.x || points[1].y != vertex2.y)
				{
					return false;
				}
				if (points[2].x != vertex3.x || points[2].y != vertex3.y)
				{
					return false;
				}
				if (lColor != outlineColor || fColor != fillColor)
				{
					return false;
				}
				return true;
			})).Exactly(fakeit::Once);
		}
	}

	WHEN("draw line")
	{
		CPoint p1 = { 10, 10 };
		CPoint p2 = { 40, 20 };
		CLineSegment line(p1, p2);
		uint32_t outlineColor = 0xFF0000;
		line.SetOutlineColor(outlineColor);

		THEN("line should call the DrawLine method with the correct parameters")
		{
			fakeit::When(Method(mockCanvas, DrawLine)).Return();
			line.Draw(mockCanvas.get());

			fakeit::Verify(Method(mockCanvas, DrawLine).Matching([&](CPoint from, CPoint to, uint32_t lColor) {
				if (from.x != p1.x || from.y != p1.y)
				{
					return false;
				}
				if (to.x != p2.x || to.y != p2.y)
				{
					return false;
				}
				if (lColor != outlineColor)
				{
					return false;
				}
				return true;
			})).Exactly(fakeit::Once);
		}
	}

	WHEN("draw circle")
	{
		CPoint center = { 25, 25 };
		double radius = 10;
		CCircle circle(center, radius);
		uint32_t outlineColor = 0xFF0000;
		uint32_t fillColor = 0x00FF00;
		circle.SetFillColor(fillColor);
		circle.SetOutlineColor(outlineColor);

		THEN("circle should call the DrawPolygon method with the correct parameters")
		{
			fakeit::When(Method(mockCanvas, DrawCircle)).Return();
			circle.Draw(mockCanvas.get());

			fakeit::Verify(Method(mockCanvas, DrawCircle).Matching([&](CPoint center_, double radius_, uint32_t lColor, uint32_t fColor) {
				if (center_.x != center.x || center_.y != center.y)
				{
					return false;
				}
				if (radius_ != radius)
				{
					return false;
				}
				if (lColor != outlineColor || fColor != fillColor)
				{
					return false;
				}
				return true;
			})).Exactly(fakeit::Once);
		}
	}
}