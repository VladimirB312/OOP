#include "Car.h"
#include "CarException.h"

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
	if (m_speed != 0 || m_gear != gear::NEUTRAL)
	{
		throw CarError("Ñar must be stopped and in neutral gear");
	}

	m_isTurnedOn = false;
}

Car::Direction Car::GetDirection()
{
	return m_direction;
}

int Car::GetGear()
{
	return m_gear;
}

int Car::GetSpeed()
{
	return m_speed;
}

bool Car::IsCorrectGearRange(int gear)
{
	return m_speed >= m_ranges[gear].first && m_speed <= m_ranges[gear].second;
}

bool Car::IsCorrectSpeedRange(int speed)
{
	return speed >= m_ranges[m_gear].first && speed <= m_ranges[m_gear].second;
}

void Car::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = Car::Direction::STANDING_STILL;
		return;
	}

	if (m_gear == gear::REVERSE)
	{
		m_direction = Car::Direction::BACKWARD;
		return;
	}

	if (m_gear != gear::NEUTRAL)
	{
		m_direction = Car::Direction::FORWARD;
	}	
}

void Car::SetGear(int gear)
{
	if (gear == m_gear)
	{
		return;
	}

	if (gear < gear::REVERSE || gear > gear::FIFTH)
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

	if (gear == gear::REVERSE && m_speed != 0)
	{
		throw GearError("Cannot reverse while moving");
	}

	if (m_direction == Car::Direction::BACKWARD && gear != gear::NEUTRAL)
	{
		throw GearError("Cannot set forward gear while moving backward");
	}

	m_gear = gear;

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

	if (m_gear == gear::NEUTRAL && speed > m_speed)
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