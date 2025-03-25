#include "Car.h"
#include "CarException.h"

namespace
{
std::unordered_map<Car::Gear, std::pair<int, int>> m_ranges = {
	{ Car::Gear::REVERSE, { 0, 20 } },
	{ Car::Gear::NEUTRAL, { 0, 150 } },
	{ Car::Gear::FIRST, { 0, 30 } },
	{ Car::Gear::SECOND, { 20, 50 } },
	{ Car::Gear::THIRD, { 30, 60 } },
	{ Car::Gear::FOURTH, { 40, 90 } },
	{ Car::Gear::FIFTH, { 50, 150 } }
};
}

bool Car::IsTurnedOn()
{
	return m_isTurnedOn;
}

void Car::TurnOnEngine()
{
	m_isTurnedOn = true;
}

void Car::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != Gear::NEUTRAL)
	{
		throw CarError("Car must be stopped and in neutral gear");
	}

	m_isTurnedOn = false;
}

Car::Direction Car::GetDirection()
{
	return m_direction;
}

int Car::GetGear()
{
	return static_cast<int>(m_gear);
}

int Car::GetSpeed()
{
	return m_speed;
}

bool Car::IsCorrectGearRange(int gear)
{
	auto ranges = m_ranges[static_cast<Gear>(gear)]; 

	return m_speed >= ranges.first && m_speed <= ranges.second;
}

bool Car::IsCorrectSpeedRange(int speed)
{
	auto ranges = m_ranges[m_gear];

	return speed >= ranges.first && speed <= ranges.second;
}

void Car::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = Car::Direction::STANDING_STILL;
		return;
	}

	if (m_gear == Gear::REVERSE)
	{
		m_direction = Car::Direction::BACKWARD;
		return;
	}

	if (m_gear != Gear::NEUTRAL)
	{
		m_direction = Car::Direction::FORWARD;
	}
}

void Car::SetGear(int gear)
{
	if (gear == static_cast<int>(m_gear))
	{
		return;
	}

	if (gear < static_cast<int>(Gear::REVERSE) || gear > static_cast<int>(Gear::FIFTH))
	{
		throw GearError("Invalid gear");
	}

	if (!m_isTurnedOn)
	{
		throw GearError("Ñannot set gear while engine is off");
	}

	if (!IsCorrectGearRange(gear) && gear != 0)
	{
		throw GearError("Unsuitable current speed");
	}

	if (gear == static_cast<int>(Gear::REVERSE) && m_speed != 0)
	{
		throw GearError("Cannot reverse while moving");
	}

	if (m_direction == Car::Direction::BACKWARD && gear != static_cast<int>(Gear::NEUTRAL))
	{
		throw GearError("Cannot set forward gear while moving backward");
	}

	m_gear = static_cast<Gear>(gear);

	SetDirection();
}

void Car::SetSpeed(int speed)
{
	if (speed == m_speed)
	{
		return;
	}

	if (speed < 0)
	{
		throw SpeedError("Speed cannot be negative");
	}

	if (!m_isTurnedOn)
	{
		throw SpeedError("Cannot set speed while engine is off");
	}

	if (m_gear == Gear::NEUTRAL && speed > m_speed)
	{
		throw SpeedError("Cannot accelerate on neutral");
	}

	if (!IsCorrectSpeedRange(speed))
	{
		throw SpeedError("Speed is out of gear range");
	}

	m_speed = speed;

	SetDirection();
}