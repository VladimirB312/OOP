#include "CarController.h"
#include "CarControllerException.h"
#include "DirectionToString.h"

namespace command
{
const std::string Info = "Info";
const std::string EngineOn = "EngineOn";
const std::string EngineOff = "EngineOff";
const std::string SetGear = "SetGear";
const std::string SetSpeed = "SetSpeed";
} // namespace command

CarController::CarController(std::istream& input, std::ostream& output, Car& car)
	: m_input(input)
	, m_output(output)
	, m_car(car)
	, m_actionMap({
		  { command::EngineOn, [this](std::istream& strm) { return EngineOn(strm); } },
		  { command::EngineOff, [this](std::istream& strm) { return EngineOff(strm); } },
		  { command::SetGear, [this](std::istream& strm) { return SetGear(strm); } },
		  { command::SetSpeed, [this](std::istream& strm) { return SetSpeed(strm); } },
		  { command::Info, [this](std::istream& strm) { return Info(strm); } },
	  })
{
}

void CarController::StartDriving()
{
	std::string line;
	while (getline(m_input, line))
	{
		std::istringstream strm(line);
		try
		{
			HandleCommand(strm);
		}
		catch (const CarControllerError& error)
		{
			m_output << error.what() << "\n";
		}
		catch (const CarError& error)
		{
			m_output << error.what() << "\n";
		}
		catch (...)
		{
			throw;
		}
	}
}

void CarController::HandleCommand(std::istream& args)
{
	std::string action;
	args >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(args);
		return;
	}

	throw CarControllerError("Unknown command");
}

void CarController::EngineOn(std::istream& /*args*/)
{
	m_car.TurnOnEngine();
}

void CarController::EngineOff(std::istream& /*args*/)
{
	m_car.TurnOffEngine();
}

void CarController::SetGear(std::istream& args)
{
	int gear;
	if (!(args >> gear))
	{
		throw CarControllerError("Invalid command argument");
	}

	m_car.SetGear(gear);
}

void CarController::SetSpeed(std::istream& args)
{
	int speed;
	if (!(args >> speed))
	{
		throw CarControllerError("Invalid command argument");
	}

	m_car.SetSpeed(speed);
}

void CarController::Info(std::istream& /*args*/)
{
	m_output << "\nEngine: " << (m_car.IsTurnedOn() ? "on" : "off") << "\n";
	m_output << "Direction: " << DirectionToString(m_car.GetDirection()) << "\n";
	m_output << "Speed: " << m_car.GetSpeed() << "\n";
	m_output << "Gear: " << m_car.GetGear() << "\n\n";
}