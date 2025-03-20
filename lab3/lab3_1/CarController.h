#pragma once
#include "Car.h"
#include "CarException.h"
#include <functional>
#include <map>
#include <sstream>

class CarController
{
public:
	CarController(std::istream& input, std::ostream& output, Car& car);
	void StartDriving();

private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;
	Car& m_car;
	const ActionMap m_actionMap;
	void HandleCommand(std::istream& args);
	void EngineOn(std::istream& args);
	void EngineOff(std::istream& args);
	void Info(std::istream& args);
	void SetGear(std::istream& args);
	void SetSpeed(std::istream& args);
};