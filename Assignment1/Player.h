/*/*****************************************************************************/
/*!
\file Player.h

\author Bryan Choo
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par Course: cs260
\par Assignment 4
\date 1/8/21

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

#pragma once
#include <string>

enum class MoveType : unsigned char;

class Player
{
public:
	// Flag to check if player has previously connected
	bool hasPreviouslyConnnected{ false };

	//Flag to check if player is currently connected
	bool isConnected{ false };

	//connection timeout
	float connectionTimer{ 0.0f };

	//player score
	int score{ 0 };

	//alive / dead
	bool alive{ true };

	MoveType moveType;
};

