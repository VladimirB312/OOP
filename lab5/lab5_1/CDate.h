#pragma once
#include "stdexcept"
#include <string>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CDateException : public std::runtime_error
{
public:
	CDateException(const std::string& message)
		: std::runtime_error(message)
	{
	}
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timestamp);
	CDate() = default;
	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate& operator--();
	CDate operator++(int);
	CDate operator--(int);
	CDate operator+(int days);
	CDate operator-(int days);

private:
	unsigned m_timestamp = 0;
	WeekDay m_weekDay = WeekDay::THURSDAY;
	Month m_month = Month::JANUARY;
	unsigned m_day = 1;
	unsigned m_year = 1970;
	void CalculateDate();
	void CalculateTimestamp();
};