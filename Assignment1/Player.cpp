#include "Player.h"

std::string Player::GetPortName() const
{
	return portName;
}
std::string Player::GetPortNumber() const
{
	return portNumber;
}

Player::Player
(const std::string& name, const std::string addressname)
	:portName{ name }, portNumber{ addressname } {}
