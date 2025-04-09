#pragma once
#include "stdexcept"
#include <format>
#include <ostream>
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
	CDate(int day, Month month, int year);
	explicit CDate(int timestamp);
	CDate() = default;
	int GetDay() const;
	Month GetMonth() const;
	int GetYear() const;
	WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate& operator--();
	CDate operator++(int);
	CDate operator--(int);
	CDate operator+(int days) const;
	CDate operator-(int days) const;
	int operator-(const CDate& date) const;
	CDate& operator+=(int days);
	CDate& operator-=(int days);

private:
	int m_timestamp = 0;
	WeekDay m_weekDay = WeekDay::THURSDAY;
	Month m_month = Month::JANUARY;
	int m_day = 1;
	int m_year = 1970;
	void CalculateDate();
	void CalculateTimestamp();
};

std::ostream& operator<<(std::ostream& stream, const CDate& date);
std::istream& operator>>(std::istream& stream, CDate& date);