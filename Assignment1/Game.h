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

#include "KinematicState.h"
#include "GameObject.h"
#include "NetworkManager.h"

class Game
{
	static NetworkManager* network;

	static void Interaction();
	static void MoveObject();
	static void MoveLighting();
	static void DeadReckoning(const float& delay = 0.05f);
	static void BlendKinematicState(KinematicState& oldState,
		KinematicState& newState,
		const float percentageToNew);

public:
	static void CheckState();
	static void Init(NetworkManager* _network);
	static void Update();
	static void InitPlayer(size_t playerID);

	static void UpdateDeadReckoning(const std::unique_ptr<GameObject>& player,
		const glm::vec3& position,
		const unsigned char& flag);
};

