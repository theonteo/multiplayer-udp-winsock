/*****************************************************************************/
/*!
\file Game.h

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
#include <vector>
class Game
{
	static void Interaction();
	static void MoveObject();
	static void MoveLighting();
	static void DeadReckoning(const float& delay = 0.05f);

public:
	static void CheckState();
	static void Update();
	static void InitPlayer(size_t playerID);
};

