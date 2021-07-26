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
public:
	//is player connected
	bool connected{ false };

	//connection timeout
	float connectionTimer{ 0.0f };

	//player score
	int score{ 0 };

	//alive / dead
	bool alive{ false };

	//player name
	std::string portName;

	//port being used
	std::string portNumber;


	/*
	float GetConnectionTimer() const;
	bool GetConnection() const;

	void SetConnectionTimer(float num);
	void SetConnection(bool connection);

	std::string GetPortName()const;
	std::string GetPortNumber() const;

	//constructor
	Player
	(const std::string& name, const std::string address);
	*/
};

