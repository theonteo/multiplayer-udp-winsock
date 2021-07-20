#pragma once
#include <string>

class Player
{
	//player name
	std::string portName;

	//port being used
	std::string portNumber;

public:

	std::string GetPortName()const;
	std::string GetPortNumber() const;

	//constructor
	Player
	(const std::string& name, const std::string address);
};

