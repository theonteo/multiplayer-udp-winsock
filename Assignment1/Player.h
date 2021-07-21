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

