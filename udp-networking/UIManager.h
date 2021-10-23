/******************************************************************************/
/*!
\file UIManager.h
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

