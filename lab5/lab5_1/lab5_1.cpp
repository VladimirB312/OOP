#include "CDate.h"
#include <iostream>

std::string WeekToStr(WeekDay day)
{
	switch (day)
	{
	case WeekDay::SUNDAY:
		return "SUNDAY";
	case WeekDay::MONDAY:
		return "MONDAY";
	case WeekDay::TUESDAY:
		return "TUESDAY";
	case WeekDay::WEDNESDAY:
		return "WEDNESDAY";
	case WeekDay::THURSDAY:
		return "THURSDAY";
	case WeekDay::FRIDAY:
		return "FRIDAY";
	case WeekDay::SATURDAY:
		return "SATURDAY";
	default:
		return "UNKNOWN DAY";
	}
}

int main()
{
	CDate date;
	date += 20;
	//CDate date(0);
	std::cout << "d: " << date.GetDay() << ", m: " << static_cast<unsigned>(date.GetMonth()) << ", y: " << date.GetYear() << "\n";
	std::cout << "week: " << WeekToStr(date.GetWeekDay()) << "\n";
}
