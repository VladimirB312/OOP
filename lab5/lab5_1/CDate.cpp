#include "CDate.h"
#include "ParseDate.h"
#include <iostream>
#include <vector>

namespace
{
namespace constants
{
constexpr int MAX_DAY = 2932896;
constexpr int MIN_DAY = 0;
constexpr int START_WEEK_DAY = 4;
constexpr int DAYS_IN_WEEK = 7;
constexpr int DAYS_BEFORE_EPOCH = 719468;
constexpr int DAYS_IN_ERA = 146097;
constexpr int DAYS_IN_CENTURY = 36524;
constexpr int DAYS_IN_4_YEARS = 1460;
constexpr int YEARS_IN_ERA = 400;
constexpr int YEARS_IN_CENTURY = 100;
constexpr int FOUR_YEARS = 4;
constexpr int DAYS_IN_YEAR = 365;
constexpr int MIN_YEAR = 1970;
constexpr int MAX_YEAR = 9999;
constexpr int LAST_DAY_OF_FEBRUARY_IN_LEAP = 29;
} // namespace constants

bool IsLeapYear(int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int LastDayOfMonth(int year, int month)
{
	std::vector<int> days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == static_cast<int>(Month::FEBRUARY) && IsLeapYear(year))
	{
		return constants::LAST_DAY_OF_FEBRUARY_IN_LEAP;
	}

	return days[month - 1];
}

void CheckDate(int day, int month, int year)
{
	if (year < constants::MIN_YEAR || year > constants::MAX_YEAR)
	{
		throw CDateException("Invalid year!");
	}

	if (month < 1 || month > 12)
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
	: CDate(CalculateTimestamp(day, static_cast<int>(month), year))
{
}

CDate::CDate(int timestamp)
{
	if (timestamp < 0 || timestamp > constants::MAX_DAY)
	{
		throw CDateException("Invalid date!");
	}

	m_timestamp = timestamp;
}

CDate::DateDTO CDate::CalculateDate() const
{
	int days = m_timestamp + constants::DAYS_BEFORE_EPOCH;
	int era = days / constants::DAYS_IN_ERA; // количество прошедних эр
	int doe = days - era * constants::DAYS_IN_ERA; // количество дней в текущей эре
	int yoe = (doe - doe / constants::DAYS_IN_4_YEARS + doe / constants::DAYS_IN_CENTURY - doe / (constants::DAYS_IN_ERA - 1)) / 365; // количество лет в текущей эре
	int year = yoe + era * constants::YEARS_IN_ERA; // всего лет (в текущей эре + всего эр * 400)
	int doy = doe - (constants::DAYS_IN_YEAR * yoe + yoe / constants::FOUR_YEARS - yoe / constants::YEARS_IN_CENTURY); // текущий номер дня
	int mp = (5 * doy + 2) / 153;
	int day = doy - (153 * mp + 2) / 5 + 1;
	int month = mp < 10 ? mp + 3 : mp - 9;
	year += month <= 2 ? 1 : 0;

	return { day, static_cast<Month>(month), year };
}

int CDate::CalculateTimestamp(int day, int month, int year)
{
	CheckDate(day, month, year);
	year -= month <= 2 ? 1 : 0;
	month = month > 2 ? month - 3 : month + 9;
	int era = year / 400;
	int yoe = year - era * 400;
	int doy = (153 * month + 2) / 5 + day - 1;
	int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

	return era * constants::DAYS_IN_ERA + doe - constants::DAYS_BEFORE_EPOCH;
}

int CDate::GetDay() const
{
	return CalculateDate().day;
}

Month CDate::GetMonth() const
{
	return CalculateDate().month;
}

int CDate::GetYear() const
{
	return CalculateDate().year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + constants::START_WEEK_DAY) % constants::DAYS_IN_WEEK);
}

CDate& CDate::operator++()
{
	if (m_timestamp == constants::MAX_DAY)
	{
		throw CDateException("Overflow error");
	}
	m_timestamp++;

	return *this;
}

CDate& CDate::operator--()
{
	if (m_timestamp == constants::MIN_DAY)
	{
		throw CDateException("Overflow error");
	}
	m_timestamp--;

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
	if ((days < 0 && m_timestamp < -days) || m_timestamp > (constants::MAX_DAY - days))
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

bool CDate::operator==(const CDate& date) const
{
	return m_timestamp == date.m_timestamp;
}

bool CDate::operator!=(const CDate& date) const
{
	return !(*this == date);
}

bool CDate::operator<(const CDate& date) const
{
	return m_timestamp < date.m_timestamp;
}

bool CDate::operator>(const CDate& date) const
{
	return m_timestamp > date.m_timestamp;
}

bool CDate::operator>=(const CDate& date) const
{
	return !(*this < date);
}

bool CDate::operator<=(const CDate& date) const
{
	return !(*this > date);
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
