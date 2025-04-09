#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CDate.h"
#include <cmath>

SCENARIO("create CDate")
{
	WHEN("create CDate without params")
	{
		CDate date;
		THEN("the date must be January 1, 1970, weekday Thursday")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with correct date params")
	{
		CDate date(8, Month::APRIL, 2025);
		THEN("the date must be April 8, 2025, weekday TUESDAY")
		{
			CHECK(date.GetDay() == 8);
			CHECK(date.GetMonth() == Month::APRIL);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("create CDate with incorrect day = 0")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(0, Month::APRIL, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day = -1")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(-1, Month::APRIL, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect year = 1969")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(1, Month::APRIL, 1969), CDateException);
		}
	}

	WHEN("create CDate with incorrect year = 10000")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(1, Month::APRIL, 10000), CDateException);
		}
	}

	WHEN("create CDate with correct year = 1970")
	{
		CDate date(1, Month::JANUARY, 1970);
		THEN("the date must be January 1, 1970, weekday THURSDAY")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with correct year = 1971")
	{
		CDate date(1, Month::APRIL, 1971);
		THEN("the date must be April 1, 1971, weekday THURSDAY")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::APRIL);
			CHECK(date.GetYear() == 1971);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with correct year = 9999")
	{
		CDate date(31, Month::DECEMBER, 9999);
		THEN("the date must be December 31, 9999, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 9999);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("create CDate with correct year = 9998")
	{
		CDate date(31, Month::DECEMBER, 9998);
		THEN("the date must be December 31, 9999, weekday THURSDAY")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 9998);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with incorrect day in january = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::JANUARY, 2025), CDateException);
		}
	}

	WHEN("create CDate with correct day in january = 31")
	{
		CDate date(31, Month::JANUARY, 2025);
		THEN("the date must be January 31, 2025, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("create CDate with incorrect day in february in a non-leap year = 29")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(29, Month::FEBRUARY, 2025), CDateException);
		}
	}

	WHEN("create CDate with correct day in february in a non-leap year = 28")
	{
		CDate date(28, Month::FEBRUARY, 2025);
		THEN("the date must be February 28, 2025, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 28);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("create CDate with correct day in february in a leap year = 29")
	{
		CDate date(29, Month::FEBRUARY, 2024);
		THEN("the date must be February 29, 2025, weekday THURSDAY")
		{
			CHECK(date.GetDay() == 29);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 2024);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with correct day in february = 29 in a leap year that's divisible by 100 and 400")
	{
		CDate date(29, Month::FEBRUARY, 2400);
		THEN("the date must be February 29, 2400, weekday SUNDAY")
		{
			CHECK(date.GetDay() == 29);
			CHECK(date.GetMonth() == Month::FEBRUARY);
			CHECK(date.GetYear() == 2400);
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("create CDate with incorrect day in february = 29 in a non-leap year that is divisible by 100, but not divisible by 400")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(29, Month::FEBRUARY, 2300), CDateException);
		}
	}

	WHEN("create CDate with correct day in march = 31")
	{
		CDate date(31, Month::MARCH, 2025);
		THEN("the date must be MARCH 31, 2025, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::MARCH);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("create CDate with incorrect day in march = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::MARCH, 2025), CDateException);
		}
	}

	WHEN("create CDate with correct day in april = 30")
	{
		CDate date(30, Month::APRIL, 2025);
		THEN("the date must be APRIL 30, 2025, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::APRIL);
			CHECK(date.GetYear() == 2025);
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("create CDate with incorrect day in april = 31")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(31, Month::APRIL, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in may = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::MAY, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in june = 31")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(31, Month::JUNE, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in july = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::JULY, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in august = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::AUGUST, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in september = 31")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(31, Month::SEPTEMBER, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in september = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::OCTOBER, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in september = 31")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(31, Month::NOVEMBER, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect day in september = 32")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, Month::DECEMBER, 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect month = 0")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, static_cast<Month>(0), 2025), CDateException);
		}
	}

	WHEN("create CDate with incorrect month = 13")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(32, static_cast<Month>(13), 2025), CDateException);
		}
	}
}

SCENARIO("testing the days of the week when creating from a date")
{
	WHEN("create CDate with date APRIL 7, 2025")
	{
		CDate date(7, Month::APRIL, 2025);
		THEN("the day of the week must be MONDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("create CDate with date APRIL 8, 2025")
	{
		CDate date(8, Month::APRIL, 2025);
		THEN("the day of the week must be TUESDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
		}
	}

	WHEN("create CDate with date APRIL 9, 2025")
	{
		CDate date(9, Month::APRIL, 2025);
		THEN("the day of the week must be WEDNESDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::WEDNESDAY);
		}
	}

	WHEN("create CDate with date APRIL 10, 2025")
	{
		CDate date(10, Month::APRIL, 2025);
		THEN("the day of the week must be THURSDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("create CDate with date APRIL 11, 2025")
	{
		CDate date(11, Month::APRIL, 2025);
		THEN("the day of the week must be FRIDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("create CDate with date APRIL 12, 2025")
	{
		CDate date(12, Month::APRIL, 2025);
		THEN("the day of the week must be SATURDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::SATURDAY);
		}
	}

	WHEN("create CDate with date APRIL 13, 2025")
	{
		CDate date(13, Month::APRIL, 2025);
		THEN("the day of the week must be SUNDAY")
		{
			CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
		}
	}
}

SCENARIO("create CDate with timestamp parameter")
{
	WHEN("timestamp parameter is 0")
	{
		CDate date(0);
		THEN("the date must be January 1, 1970, weekday Thursday")
		{
			CHECK(date.GetDay() == 1);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("timestamp parameter is 1")
	{
		CDate date(1);
		THEN("the date must be January 2, 1970, weekday Thursday")
		{
			CHECK(date.GetDay() == 2);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("timestamp parameter is -1")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(-1), CDateException);
		}
	}

	WHEN("timestamp parameter is MAX_DAY - 1 = 2932895")
	{
		CDate date(2932895);
		THEN("the date must be DECEMBER 30, 9999, weekday THURSDAY")
		{
			CHECK(date.GetDay() == 30);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 9999);
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("timestamp parameter is MAX_DAY = 2932896")
	{
		CDate date(2932896);
		THEN("the date must be DECEMBER 31, 9999, weekday FRIDAY")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 9999);
			CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		}
	}

	WHEN("timestamp parameter is MAX_DAY + 1 = 2932897")
	{
		THEN("an exception should be thrown")
		{
			CHECK_THROWS_AS(CDate(2932897), CDateException);
		}
	}
}

#ifdef NDEBUG
SCENARIO("test all valid dates")
{
	int month = 1;
	int year = 1970;
	int day = 1;
	int weekDay = 4;
	for (int i = 0; i <= 2932896; i++)
	{
		CDate date(i);
		CDate date2(day, static_cast<Month>(month), year);

		CHECK(date2.GetDay() == day);
		CHECK(date2.GetMonth() == static_cast<Month>(month));
		CHECK(date2.GetYear() == year);
		CHECK(date2.GetWeekDay() == static_cast<WeekDay>(weekDay));

		CHECK(date.GetDay() == day);
		CHECK(date.GetMonth() == static_cast<Month>(month));
		CHECK(date.GetYear() == year);
		CHECK(date.GetWeekDay() == static_cast<WeekDay>(weekDay));

		weekDay = (weekDay + 1) % 7;
		bool isLeapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
		int lastDay = 28 + (month + (month / 8)) % 2 + 2 % month + 2 * (1 / month) + (month == 2 && isLeapYear);

		if (day == lastDay)
		{
			if (month == 12)
			{
				year++;
				day = 1;
				month = 1;
				continue;
			}
			day = 1;
			month = month % 12 + 1;
			continue;
		}

		day++;
	}
}
#endif

SCENARIO("prefix increment and decrement date")
{
	GIVEN("date January 1, 1970")
	{
		CDate date;
		WHEN("incerment date")
		{
			date++;
			THEN("date will be incremented by one day")
			{
				CHECK(date.GetDay() == 2);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
			}
		}

		WHEN("create a new date and assign to it the value of the prefix increment of the current date")
		{
			CDate newDate = date++;
			THEN("new date should be equal to the old date, and the current date will be incremented by one day")
			{
				CHECK(newDate.GetDay() == 1);
				CHECK(newDate.GetMonth() == Month::JANUARY);
				CHECK(newDate.GetYear() == 1970);

				CHECK(date.GetDay() == 2);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
			}
		}

		WHEN("try to decrement date")
		{
			THEN("exception should be thrown")
			{
				CHECK_THROWS_AS(CDate(date--), CDateException);
			}
			WHEN("create a new date and try to assign to it the value of the prefix increment of the current date")
			{
				THEN("exception should be thrown")
				{
					CHECK_THROWS_AS(CDate(date--), CDateException);
				}
			}
		}
	}

	GIVEN("date December 30, 9999")
	{
		CDate date(30, Month::DECEMBER, 9999);
		WHEN("incerment date")
		{
			date++;
			THEN("date will be incremented by one day")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}

		WHEN("create a new date and assign to it the value of the prefix increment of the current date")
		{
			CDate newDate = date++;
			THEN("new date should be equal to the old date, and the current date will be incremented by one day")
			{
				CHECK(newDate.GetDay() == 30);
				CHECK(newDate.GetMonth() == Month::DECEMBER);
				CHECK(newDate.GetYear() == 9999);

				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}
	}

	GIVEN("date December 31, 9999")
	{
		CDate date(31, Month::DECEMBER, 9999);
		WHEN("try to increment date")
		{
			THEN("exception should be thrown")
			{
				CHECK_THROWS_AS(date++, CDateException);
			}
		}
		WHEN("create a new date and try to assign to it the value of the prefix increment of the current date")
		{

			THEN("exception should be thrown")
			{
				CHECK_THROWS_AS(CDate(date++), CDateException);
			}
		}

		WHEN("decrement date")
		{
			date--;
			THEN("date will be decremented by one day")
			{
				CHECK(date.GetDay() == 30);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}
		WHEN("create a new date assign to it the value of the prefix decrement of the current date")
		{
			CDate newDate = date--;
			THEN("new date should be equal to the old date, and the current date will be decremented by one day")
			{
				CHECK(newDate.GetDay() == 31);
				CHECK(newDate.GetMonth() == Month::DECEMBER);
				CHECK(newDate.GetYear() == 9999);

				CHECK(date.GetDay() == 30);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}
	}

	GIVEN("date January 31, 2024")
	{
		CDate date(31, Month::JANUARY, 2024);
		WHEN("increment date")
		{
			date++;
			THEN("date should change to the new month")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::FEBRUARY);
				CHECK(date.GetYear() == 2024);
			}
			AND_WHEN("decrement date")
			{
				date--;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 31);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 2024);
				}
			}
		}
	}

	GIVEN("date December 31, 2024")
	{
		CDate date(31, Month::DECEMBER, 2024);
		WHEN("increment date")
		{
			date++;
			THEN("date should change to the new month and year")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 2025);
			}
			AND_WHEN("decrement date")
			{
				date--;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 31);
					CHECK(date.GetMonth() == Month::DECEMBER);
					CHECK(date.GetYear() == 2024);
				}
			}
		}
	}
}

SCENARIO("addition and subtraction")
{
	GIVEN("date January 1, 1970")
	{
		CDate date;
		WHEN("add 10 days to the date")
		{
			date = date + 10;
			THEN("days should be added to the date")
			{
				CHECK(date.GetDay() == 11);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
			}

			AND_WHEN("subtract 10 days to the date")
			{
				date = date - 10;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}

			WHEN("try to subtract 11 day to the date")
			{
				THEN("an exception should be throw")
				{
					CHECK_THROWS_AS(date = date - 11, CDateException);
				}
			}
		}

		WHEN("trying to add a negative value that exceeds the allowed value")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date = date + (-1), CDateException);
			}
		}

		WHEN("add the maximum possible value = 2932896")
		{
			date = date + 2932896;
			THEN("the date will be December 31, 9999")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}

			AND_WHEN("subtract 2932896 days to the date")
			{
				date = date - 2932896;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}
		}

		WHEN("subtract the maximum possible negative value = -2932896")
		{
			date = date - -2932896;
			THEN("the date will be December 31, 9999")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}

			AND_WHEN("add maximum possible negative value -2932896 days to the date")
			{
				date = date + -2932896;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}
		}

		WHEN("try to add MAX VALUE + 1 = 2932897")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date = date + 2932897, CDateException);
			}
		}

		WHEN("try to subtract 1 day to the date")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date = date - 1, CDateException);
			}
		}
	}
}

SCENARIO("difference of two dates")
{
	WHEN("dates are equal")
	{
		CDate date1(24, Month::APRIL, 2025);
		CDate date2(24, Month::APRIL, 2025);
		THEN("their difference will be equal to 0")
		{
			CHECK(date1 - date2 == 0);
		}
	}

	WHEN("when the first date is one day beyond the second")
	{
		CDate date1(25, Month::APRIL, 2025);
		CDate date2(24, Month::APRIL, 2025);
		THEN("their difference will be equal to 1")
		{
			CHECK(date1 - date2 == 1);
		}
	}

	WHEN("when the first date is one day less than the second")
	{
		CDate date1(24, Month::APRIL, 2025);
		CDate date2(25, Month::APRIL, 2025);
		THEN("their difference will be equal to -1")
		{
			CHECK(date1 - date2 == -1);
		}
	}

	WHEN("when the first date is one year beyond the second")
	{
		CDate date1(24, Month::APRIL, 2026);
		CDate date2(24, Month::APRIL, 2025);
		THEN("their difference will be equal to 365")
		{
			CHECK(date1 - date2 == 365);
		}
	}

	WHEN("when the first date is one year less than the second")
	{
		CDate date1(24, Month::APRIL, 2025);
		CDate date2(24, Month::APRIL, 2026);
		THEN("their difference will be equal to -365")
		{
			CHECK(date1 - date2 == -365);
		}
	}
}

SCENARIO("addition and subtraction with assignment")
{
	GIVEN("date January 1, 1970")
	{
		CDate date;
		WHEN("add 10 days to the date")
		{
			date += 10;
			THEN("days should be added to the date")
			{
				CHECK(date.GetDay() == 11);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
			}

			AND_WHEN("subtract 10 days to the date")
			{
				date -= 10;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}

			WHEN("try to subtract 11 day to the date")
			{
				THEN("an exception should be throw")
				{
					CHECK_THROWS_AS(date -= 11, CDateException);
				}
			}
		}

		WHEN("trying to add a negative value that exceeds the allowed value")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date += -1, CDateException);
			}
		}

		WHEN("add the maximum possible value = 2932896")
		{
			date += 2932896;
			THEN("the date will be December 31, 9999")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}

			AND_WHEN("subtract 2932896 days to the date")
			{
				date -= 2932896;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}
		}

		WHEN("subtract the maximum possible negative value = -2932896")
		{
			date -= -2932896;
			THEN("the date will be December 31, 9999")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}

			AND_WHEN("add maximum possible negative value -2932896 days to the date")
			{
				date += -2932896;
				THEN("date should be return to start value")
				{
					CHECK(date.GetDay() == 1);
					CHECK(date.GetMonth() == Month::JANUARY);
					CHECK(date.GetYear() == 1970);
				}
			}
		}

		WHEN("try to add MAX VALUE + 1 = 2932897")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date += 2932897, CDateException);
			}
		}

		WHEN("try to subtract 1 day to the date")
		{
			THEN("an exception should be throw")
			{
				CHECK_THROWS_AS(date -= 1, CDateException);
			}
		}
	}
}

SCENARIO("date output test")
{
	std::ostringstream output;

	GIVEN("date January 1, 1970")
	{
		CDate date;
		WHEN("output the date to the stream")
		{
			output << date;
			THEN("output must contain a date in the format DD.MM.YYYY")
			{
				CHECK(output.str() == "01.01.1970");
			}
		}
	}

	GIVEN("date April 9, 2025")
	{
		CDate date(9, Month::APRIL, 2025);
		WHEN("output the date to the stream")
		{
			output << date;
			THEN("output must contain a date in the format DD.MM.YYYY")
			{
				CHECK(output.str() == "09.04.2025");
			}
		}
	}

	GIVEN("date January 31, 9999")
	{
		CDate date(31, Month::DECEMBER, 9999);
		WHEN("output the date to the stream")
		{
			output << date;
			THEN("output must contain a date in the format DD.MM.YYYY")
			{
				CHECK(output.str() == "31.12.9999");
			}
		}
	}
}

SCENARIO("date input test")
{
	GIVEN("input stream containing 05.05.1980")
	{
		std::istringstream input("05.05.1980");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date must contain the date from the input stream")
			{
				CHECK(date.GetDay() == 5);
				CHECK(date.GetMonth() == Month::MAY);
				CHECK(date.GetYear() == 1980);
			}
		}
	}

	GIVEN("input stream containing 31.12.9999")
	{
		std::istringstream input("31.12.9999");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date must contain the date from the input stream")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}
	}

	GIVEN("input stream containing 1.12.2025")
	{
		std::istringstream input("1.12.2025");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 11.2.2025")
	{
		std::istringstream input("11.2.2025");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 1.12.202")
	{
		std::istringstream input("1.12.202");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 1.1.202")
	{
		std::istringstream input("1.1.202");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing a1.12.2023")
	{
		std::istringstream input("a1.12.2023");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 11.2b.2023")
	{
		std::istringstream input("11.2b.2023");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 11.02.202b")
	{
		std::istringstream input("11.02.202b");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}

	GIVEN("input stream containing 11:02:2025")
	{
		std::istringstream input("11:02:2025");
		WHEN("read date from stream")
		{
			CDate date;
			input >> date;
			THEN("date should not change, and the stream will set an error flag")
			{
				CHECK(date.GetDay() == 01);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 1970);
				CHECK(input.fail());
			}
		}
	}
}