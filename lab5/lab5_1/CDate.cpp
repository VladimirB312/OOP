#include "CDate.h"
#include <iostream>
#include <vector>
#include "ParseDate.h"

namespace
{
const int MAX_DAY = 2932896;
const int MIN_DAY = 0;
const int START_WEEK_DAY = 4;
const int DAYS_IN_WEEK = 7;
const int DAYS_BEFORE_EPOCH = 719468;
const int DAYS_IN_ERA = 146097;
const int DAYS_IN_CENTURY = 36524;
const int DAYS_IN_4_YEARS = 1460;
const int YEARS_IN_ERA = 400;
const int YEARS_IN_CENTURY = 100;
const int FOUR_YEARS = 4;
const int DAYS_IN_YEAR = 365;
const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;
const int LAST_DAY_OF_FEBRUARY_IN_LEAP = 29;

bool IsLeapYear(int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int LastDayOfMonth(int year, Month month)
{
	std::vector<int> days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == Month::FEBRUARY && IsLeapYear(year))
	{
		return LAST_DAY_OF_FEBRUARY_IN_LEAP;
	}

	return days[static_cast<int>(month) - 1];
}

void CheckDate(int day, Month month, int year)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		throw CDateException("Invalid year!");
	}

	int monthNum = static_cast<int>(month);
	if (monthNum < 1 || monthNum > 12)
	{
		throw CDateException("Invalid month!");
	}

	if (day < 1 || day > LastDayOfMonth(year, month))
	{
		throw CDateException("Invalid day!");
	}
}
} // namespace

CDate::CDate(int day, Month month, int year)
{
	CheckDate(day, month, year);
	m_day = day;
	m_month = month;
	m_year = year;
	CalculateTimestamp();
	m_weekDay = static_cast<WeekDay>((m_timestamp + START_WEEK_DAY) % DAYS_IN_WEEK);
}

CDate::CDate(int timestamp)
{
	if (timestamp < 0 || timestamp > MAX_DAY)
	{
		throw CDateException("Invalid date!");
	}

	m_timestamp = timestamp;
	CalculateDate();
}

void CDate::CalculateDate()
{
	int days = m_timestamp + DAYS_BEFORE_EPOCH;
	int era = days / DAYS_IN_ERA; // количество прошедних эр
	int doe = days - era * DAYS_IN_ERA; // количество дней в текущей эре
	int yoe = (doe - doe / DAYS_IN_4_YEARS + doe / DAYS_IN_CENTURY - doe / (DAYS_IN_ERA - 1)) / 365; // количество лет в текущей эре
	m_year = yoe + era * YEARS_IN_ERA; // всего лет (в текущей эре + всего эр * 400)
	int doy = doe - (DAYS_IN_YEAR * yoe + yoe / FOUR_YEARS - yoe / YEARS_IN_CENTURY); // текущий номер дня
	int mp = (5 * doy + 2) / 153;
	m_day = doy - (153 * mp + 2) / 5 + 1;
	int month = mp < 10 ? mp + 3 : mp - 9;
	m_year += month <= 2 ? 1 : 0;
	m_month = static_cast<Month>(month);
	m_weekDay = static_cast<WeekDay>((m_timestamp + START_WEEK_DAY) % DAYS_IN_WEEK);
}

void CDate::CalculateTimestamp()
{
	int month = static_cast<int>(m_month);
	int year = m_year;
	year -= month <= 2 ? 1 : 0;
	month = month > 2 ? month - 3 : month + 9;
	int era = year / 400;
	int yoe = year - era * 400;
	int doy = (153 * month + 2) / 5 + m_day - 1;
	int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	m_timestamp = era * DAYS_IN_ERA + doe - DAYS_BEFORE_EPOCH;
}

int CDate::GetDay() const
{
	return m_day;
}

Month CDate::GetMonth() const
{
	return m_month;
}

int CDate::GetYear() const
{
	return m_year;
}

WeekDay CDate::GetWeekDay() const
{
	return m_weekDay;
}

CDate& CDate::operator++()
{
	if (m_timestamp == MAX_DAY)
	{
		throw CDateException("Overflow error");
	}
	m_timestamp++;
	CalculateDate();

	return *this;
}

CDate& CDate::operator--()
{
	if (m_timestamp == MIN_DAY)
	{
		throw CDateException("Overflow error");
	}
	m_timestamp--;
	CalculateDate();

	return *this;
}

CDate CDate::operator++(int)
{
	CDate copy{ *this };
	++(*this);

	return copy;
}

CDate CDate::operator--(int)
{
	CDate copy{ *this };
	--(*this);

	return copy;
}

CDate CDate::operator+(int days) const
{
	if ((days < 0 && m_timestamp < -days) || m_timestamp > (MAX_DAY - days))
	{
		throw CDateException("Overflow error");
	}

	CDate newDate(m_timestamp + days);

	return newDate;
}

CDate CDate::operator-(int days) const
{
	return (*this) + (-days);
}

int CDate::operator-(const CDate& date) const
{
	return m_timestamp - date.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
	*this = (*this) + days;
	return *this;
}

CDate& CDate::operator-=(int days)
{
	*this = (*this) - days;
	return *this;
}

std::ostream& operator<<(std::ostream& stream, const CDate& date)
{
	stream << std::format("{:02}", date.GetDay()) << ".";
	stream << std::format("{:02}", static_cast<int>(date.GetMonth())) << ".";
	stream << date.GetYear();

	return stream;
}

std::istream& operator>>(std::istream& stream, CDate& date)
{
	int day;
	int month;
	int year;
	
	std::string dateStr;
	stream >> dateStr;
	if (ParseDate(dateStr, day, month, year))
	{
		date = CDate(day, static_cast<Month>(month), year);		
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}
