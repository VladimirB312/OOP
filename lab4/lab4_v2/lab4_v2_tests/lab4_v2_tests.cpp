#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CCircle.h"
#include "../CLineSegment.h"
#include "../CPoint.h"
#include "../CRectangle.h"
#include "../CTriangle.h"
#include "../ShapeStorage.h"

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
		THEN("area should be 209, perimeter 60, width, height")
		{
			CHECK_THAT(rect.GetArea(), Catch::Matchers::WithinAbs(209, 0.001));
			CHECK_THAT(rect.GetPerimeter(), Catch::Matchers::WithinAbs(60, 0.001));
			CHECK_THAT(rect.GetWidth(), Catch::Matchers::WithinAbs(11, 0.001));
			CHECK_THAT(rect.GetHeight(), Catch::Matchers::WithinAbs(19, 0.001));
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
}

SCENARIO("get max area and min perimeter")
{
	GIVEN("shape storage with several shapes, where the circle with maximum area and the line with minimum perimeter")
	{
		ShapeStorage storage;
		auto line = std::make_shared<CLineSegment>(CPoint{ 1, 3 }, CPoint{ 3, 5 });
		auto triangle = std::make_shared<CTriangle>(CPoint{ 1, 2 }, CPoint{ 7, 2 }, CPoint{ 3, 8 });
		auto rect = std::make_shared<CRectangle>(CPoint{ 0, 0 }, CPoint{ 15, 15 });
		auto circle = std::make_shared<CCircle>(CPoint{ 10, 10 }, 15);
		storage.AddShape(line);
		storage.AddShape(triangle);
		storage.AddShape(rect);
		storage.AddShape(circle);

		WHEN("get shape with a maximum area")
		{
			auto shape = storage.GetMaxAreaShape().value();
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
			auto shape = storage.GetMinPerimeterShape().value();
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
		ShapeStorage storage;
		auto line = std::make_shared<CLineSegment>(CPoint{ 2, 2 }, CPoint{ 100, 9 });
		auto triangle = std::make_shared<CTriangle>(CPoint{ 4, 3 }, CPoint{ 10, 4 }, CPoint{ 5, 10 });
		auto rect = std::make_shared<CRectangle>(CPoint{ 10, 10 }, CPoint{ 30, 30 });
		auto circle = std::make_shared<CCircle>(CPoint{ 2, 2 }, 4);
		storage.AddShape(line);
		storage.AddShape(triangle);
		storage.AddShape(rect);
		storage.AddShape(circle);

		WHEN("get shape with a maximum area")
		{
			auto shape = storage.GetMaxAreaShape().value();
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
			auto shape = storage.GetMinPerimeterShape().value();
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