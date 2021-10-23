/******************************************************************************/
/*!
\file Game.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

