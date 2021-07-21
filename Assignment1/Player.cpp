/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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
