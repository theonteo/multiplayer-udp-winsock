/******************************************************************************/
/*!
\file Game.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par email: c.choo\@digipen.edu
\par email: kevin.hartono\@digipen.edu
\par email: zhengyongtheon.teo\@digipen.edu

\par DigiPen login: c.choo
\par DigiPen login: kevin.hartono
\par DigiPen login: zhengyongtheon.teo

\par Course: CS260-A
\par Assignment 4
\date 01/08/2021
\brief
This file contains the declarations of the main game driver class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/
#pragma once

#include <string>
#include <vector>
#include "NetworkManager.h"

class Game
{
	static NetworkManager* network;
	static float gameTime;

	static void Interaction();
	static void MoveObject();
	static void MoveLighting();
	static void DeadReckoning(const float& delay = 0.05f);

public:
	static void CheckState();
	static void Init(NetworkManager* _network);
	static void Update();
	static void InitPlayer(size_t playerID);

	static float GetGameTime();
	static void SetGameTime(float _gameTime);
	static glm::vec3 CreateVectorFromFlag(unsigned char flag);
};

