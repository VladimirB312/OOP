#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Car.h"
#include "../CarException.h"

SCENARIO("Turn on and turn off car")
{
	Car car;

	GIVEN("turned off car")
	{
		CHECK(!car.IsTurnedOn());
		CHECK(car.GetDirection() == Car::Direction::STANDING_STILL);
		CHECK(car.GetGear() == 0);
		CHECK(car.GetSpeed() == 0);

		WHEN("turn on car")
		{
			car.TurnOnEngine();
			THEN("the car should turn on, gear should be 0, direction should be STANDING_STILL and speed should be 0")
			{
				CHECK(car.IsTurnedOn());
			}

			AND_WHEN("car is turned off")
			{
				car.TurnOffEngine();
				THEN("the car should turn off")
				{
					CHECK(!car.IsTurnedOn());
				}
			}
		}
	}

	GIVEN("turned on car")
	{
		car.TurnOnEngine();
		WHEN("set gear to first and try to turn off car")
		{
			car.SetGear(gear::FIRST);
			THEN("error car must be stopped and in neutral gear should be thrown")
			{
				CHECK_THROWS_AS(car.TurnOffEngine(), CarError);
			}
		}

		WHEN("set gear to reverse and try to turn off car")
		{
			car.SetGear(gear::REVERSE);
			THEN("error car must be stopped and in neutral gear should be thrown")
			{
				CHECK_THROWS_AS(car.TurnOffEngine(), CarError);
			}
		}

		WHEN("first gain speed and then set gear to neutral and try to turn off car")
		{
			car.SetGear(gear::FIRST);
			car.SetSpeed(20);
			car.SetGear(gear::NEUTRAL);
			THEN("error car must be stopped and in neutral gear should be thrown")
			{
				CHECK_THROWS_AS(car.TurnOffEngine(), CarError);
			}
		}

		WHEN("first gain reverse speed and then set gear to 0 and try to turn off car")
		{
			car.SetGear(gear::REVERSE);
			car.SetSpeed(20);
			car.SetGear(gear::NEUTRAL);
			THEN("error car must be stopped and in neutral gear should be thrown")
			{
				CHECK_THROWS_AS(car.TurnOffEngine(), CarError);
			}
		}
	}
}

SCENARIO("set gear")
{
	Car car;

	GIVEN("turned off car")
	{
		WHEN("try to switch to first gear")
		{
			THEN("error set gear while engine is off should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIRST), GearError);
			}
		}

		WHEN("try ty switch to reverse gear")
		{
			THEN("error set gear while engine is off should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::REVERSE), GearError);
			}
		}
	}

	GIVEN("turned on car")
	{
		car.TurnOnEngine();
		WHEN("switch to first gear")
		{
			car.SetGear(gear::FIRST);
			THEN("first gear should engage")
			{
				CHECK(car.GetGear() == gear::FIRST);
			}
		}

		WHEN("switch to reverse gear")
		{
			car.SetGear(gear::REVERSE);
			THEN("reverse gear should engage")
			{
				CHECK(car.GetGear() == gear::REVERSE);
			}
		}

		WHEN("switch to -2 gear")
		{
			THEN("error invalid gear should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(-2), GearError);
			}
		}

		WHEN("switch to 6 gear")
		{
			THEN("error invalid gear should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(6), GearError);
			}
		}

		WHEN("first gain speed and then set gear to neutral and try to set gear to reverse")
		{
			car.SetGear(gear::FIRST);
			car.SetSpeed(20);
			car.SetGear(gear::NEUTRAL);
			THEN("error cannot reverse while moving should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::REVERSE), CarError);
			}
		}

		WHEN("first gain reverse speed and then set gear to neutral and try to set gear to reverse")
		{
			car.SetGear(gear::REVERSE);
			car.SetSpeed(20);
			car.SetGear(gear::NEUTRAL);
			THEN("error cannot reverse while moving should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::REVERSE), CarError);
			}
		}
	}
}

SCENARIO("Set speed and gear")
{
	Car car;
	GIVEN("turned off car")
	{
		WHEN("try to set speed")
		{
			THEN("error cannot set speed while engine is off should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(10), SpeedError);
			}
		}
	}

	GIVEN("turned on car with neutral gear")
	{
		car.TurnOnEngine();
		WHEN("try to set a speed on neutral gear")
		{
			THEN("error cannot accelerate on neutral should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(10), SpeedError);
			}
		}
	}

	GIVEN("turned on car with with first gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(0);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(1);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 1);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(30);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 30);
			}
		}

		WHEN("try to set a negative speed")
		{
			THEN("error speed cannot be negative should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(-1), SpeedError);
			}
		}

		WHEN("try to set a speed that is outside the permissible range")
		{
			THEN("error speed is out of gear range should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(31), SpeedError);
			}
		}

		WHEN("set speed 19 and set second gear ")
		{
			car.SetSpeed(19);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::SECOND), GearError);
			}
		}

		WHEN("set speed 20 and set second gear ")
		{
			car.SetSpeed(20);
			car.SetGear(gear::SECOND);
			THEN("gear should be second")
			{
				CHECK(car.GetGear() == gear::SECOND);
			}
		}
	}

	GIVEN("turned on car with with reverse gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::REVERSE);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(0);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 0);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(1);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 1);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(20);
			THEN("car speed should be changed to this speed")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}

		WHEN("try to set a negative speed")
		{
			THEN("error speed cannot be negative should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(-1), SpeedError);
			}
		}

		WHEN("try to set a speed that is outside the permissible range")
		{
			THEN("error speed is out of gear range should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(21), SpeedError);
			}
		}
	}

	GIVEN("car with speed 15 on reverse gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::REVERSE);
		car.SetSpeed(15);

		WHEN("set neutral gear")
		{
			car.SetGear(gear::NEUTRAL);
			THEN("car gear should be neutral")
			{
				CHECK(car.GetGear() == gear::NEUTRAL);
			}
			AND_WHEN("reduce speed")
			{
				car.SetSpeed(10);
				THEN("car speed should be reduced")
				{
					CHECK(car.GetSpeed() == 10);
				}
			}
			AND_WHEN("try to increase speed")
			{
				THEN("error cannot accelerate on neutral should be thrown")
				{
					CHECK_THROWS_AS(car.SetSpeed(20), SpeedError);
				}
			}
		}

		WHEN("try to set first gear")
		{
			THEN("error cannot set forward gear while moving backward should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIRST), GearError);
			}
		}
	}

	GIVEN("car with speed 15 on first gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);
		car.SetSpeed(15);
		WHEN("try to set backward gear")
		{
			THEN("error cannot reverse while moving should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::REVERSE), GearError);
			}
		}

		WHEN("reduce speed to 10")
		{
			car.SetSpeed(10);
			THEN("car speed should be reduced to 10")
			{
				CHECK(car.GetSpeed() == 10);
			}
		}

		WHEN("increase speed to 20")
		{
			car.SetSpeed(20);
			THEN("car speed should be reduced to 20")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}
	}
}