#pragma once
#include <unordered_map>

class Car
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		STANDING_STILL
	};

	enum class Gear
	{
		REVERSE = -1,
		NEUTRAL,
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH
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
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
	Direction m_direction = Direction::STANDING_STILL;

	void SetDirection();
	bool IsCorrectGearRange(int gear);
	bool IsCorrectSpeedRange(int speed);
};