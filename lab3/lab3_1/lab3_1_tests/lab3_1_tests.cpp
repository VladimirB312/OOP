#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Car.h"
#include "../CarController.h"
#include "../CarControllerException.h"
#include "../CarException.h"
#include <sstream>

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
			THEN("car speed should be 0 and direction should be stand still")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetDirection() == Car::Direction::STANDING_STILL);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(1);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 1);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
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

		WHEN("set speed 30 and set second gear ")
		{
			car.SetSpeed(30);
			car.SetGear(gear::SECOND);
			THEN("gear should be second")
			{
				CHECK(car.GetGear() == gear::SECOND);
			}
		}
	}

	GIVEN("turned on car with with second gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(gear::SECOND);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(20);
			THEN("car speed should be changed to this speed and direction should be stand still")
			{
				CHECK(car.GetSpeed() == 20);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(50);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 50);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
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
				CHECK_THROWS_AS(car.SetSpeed(19), SpeedError);
			}
		}

		WHEN("set speed 40 and set first gear ")
		{
			car.SetSpeed(40);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIRST), GearError);
			}
		}

		WHEN("set speed 29 and set third gear ")
		{
			car.SetSpeed(29);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::THIRD), GearError);
			}
		}

		WHEN("set speed 31 and set third gear ")
		{
			car.SetSpeed(31);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIRST), GearError);
			}
		}

		WHEN("set speed 40 and set third gear ")
		{
			car.SetSpeed(40);
			car.SetGear(gear::THIRD);
			THEN("gear should be THIRD")
			{
				CHECK(car.GetGear() == gear::THIRD);
			}
		}

		WHEN("set speed 30 and set first gear ")
		{
			car.SetSpeed(30);
			car.SetGear(gear::FIRST);
			THEN("gear should be first")
			{
				CHECK(car.GetGear() == gear::FIRST);
			}
		}
	}

	GIVEN("turned on car with with third gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(gear::THIRD);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(40);
			THEN("car speed should be changed to this speed and direction should be stand still")
			{
				CHECK(car.GetSpeed() == 40);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(30);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 30);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(60);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 60);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
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
				CHECK_THROWS_AS(car.SetSpeed(29), SpeedError);
			}
		}

		WHEN("try to set a speed that is outside the permissible range")
		{
			THEN("error speed is out of gear range should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(61), SpeedError);
			}
		}

		WHEN("set speed 51 and set second gear ")
		{
			car.SetSpeed(51);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::SECOND), GearError);
			}
		}

		WHEN("set speed 39 and set fourth gear ")
		{
			car.SetSpeed(39);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FOURTH), GearError);
			}
		}

		WHEN("set speed 40 and set third gear ")
		{
			car.SetSpeed(40);
			car.SetGear(gear::FOURTH);
			THEN("gear should be THIRD")
			{
				CHECK(car.GetGear() == gear::FOURTH);
			}
		}

		WHEN("set speed 30 and set first gear ")
		{
			car.SetSpeed(30);
			car.SetGear(gear::FIRST);
			THEN("gear should be first")
			{
				CHECK(car.GetGear() == gear::FIRST);
			}
		}
	}

	GIVEN("turned on car with with fourth gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(gear::FOURTH);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(40);
			THEN("car speed should be changed to this speed and direction should be stand still")
			{
				CHECK(car.GetSpeed() == 40);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(90);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 90);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
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
				CHECK_THROWS_AS(car.SetSpeed(39), SpeedError);
			}
		}

		WHEN("try to set a speed that is outside the permissible range")
		{
			THEN("error speed is out of gear range should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(91), SpeedError);
			}
		}

		WHEN("set speed 611 and set third gear ")
		{
			car.SetSpeed(61);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::THIRD), GearError);
			}
		}

		WHEN("set speed 49 and set fifth gear ")
		{
			car.SetSpeed(49);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIFTH), GearError);
			}
		}

		WHEN("set speed 40 and set third gear ")
		{
			car.SetSpeed(40);
			car.SetGear(gear::THIRD);
			THEN("gear should be third")
			{
				CHECK(car.GetGear() == gear::THIRD);
			}
		}

		WHEN("set speed 50 and set first gear ")
		{
			car.SetSpeed(50);
			car.SetGear(gear::FIFTH);
			THEN("gear should be first")
			{
				CHECK(car.GetGear() == gear::FIFTH);
			}
		}
	}

	GIVEN("turned on car with with fifth gear")
	{
		car.TurnOnEngine();
		car.SetGear(gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(gear::FIFTH);

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(50);
			THEN("car speed should be changed to this speed and direction should be stand still")
			{
				CHECK(car.GetSpeed() == 50);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(150);
			THEN("car speed should be changed to this speed and direction should be forward")
			{
				CHECK(car.GetSpeed() == 150);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
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
				CHECK_THROWS_AS(car.SetSpeed(49), SpeedError);
			}
		}

		WHEN("try to set a speed that is outside the permissible range")
		{
			THEN("error speed is out of gear range should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(151), SpeedError);
			}
		}

		WHEN("set speed 91 and set fourth gear ")
		{
			car.SetSpeed(91);
			THEN("error should speed is out of gear range be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FOURTH), GearError);
			}
		}

		WHEN("set speed 90 and set fourth gear ")
		{
			car.SetSpeed(90);
			car.SetGear(gear::FOURTH);
			THEN("gear should be fourth")
			{
				CHECK(car.GetGear() == gear::FOURTH);
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
			THEN("car speed should be 0 and direction should be standing still")
			{
				CHECK(car.GetSpeed() == 0);
				CHECK(car.GetDirection() == Car::Direction::STANDING_STILL);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(1);
			THEN("car speed should be changed to this speed and direction should be backward")
			{
				CHECK(car.GetSpeed() == 1);
				CHECK(car.GetDirection() == Car::Direction::BACKWARD);
			}
		}

		WHEN("try to set a speed in permissible range")
		{
			car.SetSpeed(20);
			THEN("car speed should be changed to this speed and direction should be backward")
			{
				CHECK(car.GetSpeed() == 20);
				CHECK(car.GetDirection() == Car::Direction::BACKWARD);
			}

			AND_WHEN("reduce speed to 0 and switch first gear")
			{
				car.SetSpeed(0);
				car.SetGear(gear::FIRST);
				THEN("car gear should be first, speed should 0 and direction should be standing still")
				{
					CHECK(car.GetGear() == gear::FIRST);
					CHECK(car.GetSpeed() == 0);
					CHECK(car.GetDirection() == Car::Direction::STANDING_STILL);
				}

				AND_WHEN("increase speed to 20")
				{
					car.SetSpeed(20);
					THEN("speed should 20 and direction should be forward")
					{
						CHECK(car.GetSpeed() == 20);
						CHECK(car.GetDirection() == Car::Direction::FORWARD);
					}
				}
			}
		}

		WHEN("try to set a negative speed")
		{
			THEN("error speed cannot be negative should be thrown")
			{
				CHECK_THROWS_AS(car.SetSpeed(-1), SpeedError);
			}
		}

		WHEN("try to set a speed 1 and switch first gear")
		{
			car.SetSpeed(1);
			THEN("error speed cannot be negative should be thrown")
			{
				CHECK_THROWS_AS(car.SetGear(gear::FIRST), GearError);
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
			THEN("car gear should be neutral and direction should be backward")
			{
				CHECK(car.GetGear() == gear::NEUTRAL);
				CHECK(car.GetDirection() == Car::Direction::BACKWARD);
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
			THEN("car speed should be reduced to 20 and direction should be forward")
			{
				CHECK(car.GetSpeed() == 20);
				CHECK(car.GetDirection() == Car::Direction::FORWARD);
			}

			AND_WHEN("reduce speed to 0 and switch to reverse speed")
			{
				car.SetSpeed(0);
				car.SetGear(gear::REVERSE);
				THEN("gear should be reverse, speed should be 0 and direction should be standing still")
				{
					CHECK(car.GetGear() == gear::REVERSE);
					CHECK(car.GetSpeed() == 0);
					CHECK(car.GetDirection() == Car::Direction::STANDING_STILL);
				}

				AND_WHEN("increase speed to 20")
				{
					car.SetSpeed(20);
					THEN("speed should be 20 and direction should be backward")
					{
						CHECK(car.GetSpeed() == 20);
						CHECK(car.GetDirection() == Car::Direction::BACKWARD);
					}
				}
			}
		}
	}
}

SCENARIO("acceleration to 150 at higher speeds")
{
	Car car;
	car.TurnOnEngine();

	GIVEN("turned on car")
	{
		WHEN("switch to first gear and increase speed to 30")
		{
			car.SetGear(gear::FIRST);
			car.SetSpeed(30);
			THEN("car gear should be first and spead should be 30")
			{
				CHECK(car.GetGear() == gear::FIRST);
				CHECK(car.GetSpeed() == 30);
			}

			AND_WHEN("switch to second speed and increase speed to 50")
			{
				car.SetGear(gear::SECOND);
				car.SetSpeed(50);
				THEN("car gear should be second and spead should be 50")
				{
					CHECK(car.GetGear() == gear::SECOND);
					CHECK(car.GetSpeed() == 50);
				}

				AND_WHEN("switch to third speed and increase speed to 60")
				{
					car.SetGear(gear::THIRD);
					car.SetSpeed(60);
					THEN("car gear should be third and spead should be 60")
					{
						CHECK(car.GetGear() == gear::THIRD);
						CHECK(car.GetSpeed() == 60);
					}

					AND_WHEN("switch to fourth speed and increase speed to 90")
					{
						car.SetGear(gear::FOURTH);
						car.SetSpeed(90);
						THEN("car gear should be fourth and spead should be 90")
						{
							CHECK(car.GetGear() == gear::FOURTH);
							CHECK(car.GetSpeed() == 90);
						}

						AND_WHEN("switch to fifth speed and increase speed to 150")
						{
							car.SetGear(gear::FIFTH);
							car.SetSpeed(150);
							THEN("car gear should be fourth and spead should be 90")
							{
								CHECK(car.GetGear() == gear::FIFTH);
								CHECK(car.GetSpeed() == 150);
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("acceleration to 150 at low speeds")
{
	Car car;
	car.TurnOnEngine();

	GIVEN("turned on car")
	{
		WHEN("switch to first gear and increase speed to 20")
		{
			car.SetGear(gear::FIRST);
			car.SetSpeed(20);
			THEN("car gear should be first and spead should be 20")
			{
				CHECK(car.GetGear() == gear::FIRST);
				CHECK(car.GetSpeed() == 20);
			}

			AND_WHEN("switch to second speed and increase speed to 30")
			{
				car.SetGear(gear::SECOND);
				car.SetSpeed(30);
				THEN("car gear should be second and spead should be 30")
				{
					CHECK(car.GetGear() == gear::SECOND);
					CHECK(car.GetSpeed() == 30);
				}

				AND_WHEN("switch to third speed and increase speed to 40")
				{
					car.SetGear(gear::THIRD);
					car.SetSpeed(40);
					THEN("car gear should be third and spead should be 40")
					{
						CHECK(car.GetGear() == gear::THIRD);
						CHECK(car.GetSpeed() == 40);
					}

					AND_WHEN("switch to fourth speed and increase speed to 50")
					{
						car.SetGear(gear::FOURTH);
						car.SetSpeed(50);
						THEN("car gear should be fourth and spead should be 50")
						{
							CHECK(car.GetGear() == gear::FOURTH);
							CHECK(car.GetSpeed() == 50);
						}

						AND_WHEN("switch to fifth speed and increase speed to 150")
						{
							car.SetGear(gear::FIFTH);
							car.SetSpeed(150);
							THEN("car gear should be fourth and spead should be 90")
							{
								CHECK(car.GetGear() == gear::FIFTH);
								CHECK(car.GetSpeed() == 150);
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("Start driving")
{
	Car car;
	std::ostringstream output;

	WHEN("input commands is empty")
	{
		std::istringstream input("");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be empty too")
		{
			CHECK(output.str().empty());
		}
	}

	WHEN("input commands contain unknown command")
	{
		std::istringstream input("unknw cmd");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be contains error Unknown command")
		{
			CHECK(output.str() == "Unknown command\n");
		}
	}

	WHEN("input commands contains command EngineOn and invalid SetGear argument")
	{
		std::istringstream input("EngineOn\nSetGear A");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be contains error Invalid command argument")
		{
			CHECK(output.str() == "Invalid command argument\n");
		}
	}

	WHEN("input commands contains commands that attempt to stop the engine at a speed other than neutral")
	{
		std::istringstream input("EngineOn\nSetGear 1\nSetSpeed 10\nEngineOff");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be contains info about turned off car")
		{
			CHECK(output.str() == "Car must be stopped and in neutral gear\n");
		}
	}

	WHEN("input commands contains only Info")
	{
		std::istringstream input("Info");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be contains info about turned off car")
		{
			std::string result = "\nEngine: off\nDirection: standing still\nSpeed: 0\nGear: 0\n\n";
			CHECK(output.str() == result);
		}
	}

	WHEN("input commands contains commands to decrease speed in neutral gear")
	{
		std::istringstream input("EngineOn\nSetGear 1\nSetSpeed 30\nSetGear 0\nSetSpeed 10\nInfo");
		CarController carController(input, output, car);
		carController.StartDriving();
		THEN("output should be contains info about car")
		{
			std::string result = "\nEngine: on\nDirection: forward\nSpeed: 10\nGear: 0\n\n";
			CHECK(output.str() == result);
		}
	}
}