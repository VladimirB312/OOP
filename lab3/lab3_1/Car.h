#pragma once
#include <unordered_map>

namespace gear
{
const int REVERSE = -1;
const int NEUTRAL = 0;
const int FIRST = 1;
const int SECOND = 2;
const int THIRD = 3;
const int FOURTH = 4;
const int FIFTH = 5;
} // namespace gear

class Car
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		STANDING_STILL
	};

	bool IsTurnedOn();
	void TurnOnEngine();
	void TurnOffEngine();
	Direction GetDirection();
	int GetGear();
	int GetSpeed();
	void SetGear(int gear);
	void SetSpeed(int speed);

private:
	bool m_isTurnedOn = false;
	int m_gear = gear::NEUTRAL;
	int m_speed = 0;
	Direction m_direction = Direction::STANDING_STILL;
	std::unordered_map<int, std::pair<int, int>> m_ranges = {
		{ gear::REVERSE, { 0, 20 } },
		{ gear::NEUTRAL, { 0, 150 } },
		{ gear::FIRST, { 0, 30 } },
		{ gear::SECOND, { 20, 50 } },
		{ gear::THIRD, { 30, 60 } },
		{ gear::FOURTH, { 40, 90 } },
		{ gear::FIFTH, { 50, 150 } }
	};

	void SetDirection();
	bool IsCorrectGearRange(int gear);
	bool IsCorrectSpeedRange(int speed);
};