/*****************************************************************************/
/*!
\file UIManager.h

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
#include "NetworkManager.h"

class Player;
class UIManager
{
	
	void RenderLobby(const NetworkManager::PlayerArray& data);
	void RenderGame(const NetworkManager::PlayerArray& data);
	void RenderResult(const NetworkManager::PlayerArray& data);

public:

	void Init();
	static void InitPlayer(size_t playerID);
	void Render(const NetworkManager::PlayerArray& data);
};

